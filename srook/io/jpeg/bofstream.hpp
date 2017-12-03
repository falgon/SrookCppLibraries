#ifndef INCLUDED_SROOK_IOS_JPEG_BOFSTREAM_BIT_HPP
#define INCLUDED_SROOK_IOS_JPEG_BOFSTREAM_BIT_HPP
#include<srook/config/noexcept_detection.hpp>
#include<srook/cstddef/byte.hpp>
#include<fstream>
#include<string_view>
#include<type_traits>
#include<srook/array.hpp>
#include<memory>
#include<srook/type_traits/has_iterator.hpp>
#include<cstring>

namespace srook{
namespace io {
namespace jpeg {
inline namespace v1 {

struct bofstream final : std::ofstream{
	using std::ofstream::ofstream;

	explicit bofstream(std::size_t buffer_size,const char* filename,const std::ios_base::openmode& open_mode)
		:std::ofstream(filename,open_mode),
		buffer(std::make_unique<srook::byte[]>(buffer_size)),
		first(buffer.get()),last(buffer.get()+buffer_size),
		forward_iter(buffer.get())
	{}

	std::size_t capacity()const noexcept{return last - first;}
	std::size_t wrote_size()const noexcept{return forward_iter - first;}
	
	void output_file()
	SROOK_NOEXCEPT(write(reinterpret_cast<const char*>(std::declval<srook::byte>()),wrote_size()))
	{
		write(reinterpret_cast<const char*>(first),wrote_size());
	}
private:
	struct tag_argument{
		explicit constexpr tag_argument(int num):n(std::move(num)){}
		int n;
	};
public:	
	static constexpr auto Byte = []{};
	static constexpr auto Word = []{};
	static constexpr auto Bytes = []{};

	struct Byte_n : tag_argument{
		using tag_argument::tag_argument;
	};
	struct Bits : tag_argument{
		using tag_argument::tag_argument;
	};
private:
	std::unique_ptr<srook::byte[]> buffer;
	const srook::byte* first,*last;
	srook::byte* forward_iter;

	int bit_position = 7u;
	const srook::array<srook::byte,8> bit_fullmask{srook::byte(0x01),srook::byte(0x03),srook::byte(0x07),srook::byte(0x0f),srook::byte(0x1f),srook::byte(0x3f),srook::byte(0x7f),srook::byte(0xff)};
	bool writable = true;

	void increment_buffer()noexcept
	{
		if(++forward_iter >= last){
			writable = false;
		}
	}	

	void set_fullbit()
	SROOK_NOEXCEPT(write_fewbits(std::declval<srook::byte>(),int()))
	{
		if(bit_position != 7){
			write_fewbits(bit_fullmask[bit_position],bit_position + 1);
		}
	}
		
	void write8bits(srook::byte value,int bit_size)
	SROOK_NOEXCEPT(
			noexcept(write_fewbits(std::declval<srook::byte>(),int()))
			and
			noexcept(write_bridge(std::declval<srook::byte>(),int()))
	)
	{
		if(bit_position + 1 >= bit_size){
			write_fewbits(value,bit_size);
		}else{
			write_bridge(value,bit_size);
		}
	}
		
	void write_fewbits(srook::byte value,int bit_size)
	SROOK_NOEXCEPT(increment_buffer())
	{
		value &= bit_fullmask[bit_size-1];
		*forward_iter |= (value << (bit_position + 1 - bit_size));
		if((bit_position -= bit_size) < 0){
			if(*forward_iter == srook::byte(0xff)){
				increment_buffer();
				*forward_iter = srook::byte(0);
			}
			increment_buffer();
			bit_position = 7;
		}
	}

	void write_bridge(srook::byte value,int bit_size)
	SROOK_NOEXCEPT(increment_buffer())
	{
		value &= bit_fullmask[bit_size-1];
		int next_bits = bit_size - (bit_position + 1);
		*forward_iter |= ((value >> next_bits) & bit_fullmask[bit_position]);
		if(*forward_iter == srook::byte(0xff)){
			increment_buffer();
			*forward_iter = srook::byte(0);
		}
		increment_buffer();
		*forward_iter = (value << (8 - next_bits));
		bit_position = 7 - next_bits;
	}

	template<class T,std::size_t v>
	friend std::pair<const decltype(Bytes)&,bofstream&>
	operator<<(std::pair<const decltype(Bytes)&,bofstream&> p,const srook::array<T,v>& ar)
	noexcept(false)
	{
		if(p.second.forward_iter+ar.size() < p.second.last){
			p.second.set_fullbit();
			std::memcpy(p.second.forward_iter,ar.data(),ar.size());
			p.second.forward_iter += ar.size();
		}else{
			throw std::runtime_error(__func__);
		}
		return p;
	}

	template<class T>
	friend std::pair<const decltype(Byte)&,bofstream&>
   	operator<<(std::pair<const decltype(Byte)&,bofstream&> p,T&& src)
	noexcept(false)
	{
		if(p.second.writable){
			p.second.set_fullbit();
			*p.second.forward_iter = srook::byte(src);
			p.second.increment_buffer();
		}else{
			throw std::runtime_error(__func__);
		}
		return p;
	}

	friend std::pair<const decltype(Word)&,bofstream&> 
	operator<<(std::pair<const decltype(Word)&,bofstream&> p,unsigned int value)
	noexcept(false)
	{
		if(p.second.writable){
			p.second.set_fullbit();
			*p.second.forward_iter = srook::byte((value >> 8) & 0xff);
			p.second.increment_buffer();
			*p.second.forward_iter = srook::byte(value & 0xff);
			p.second.increment_buffer();
		}else{
			throw std::runtime_error(__func__);
		}
		return p;
	}

	friend std::pair<Bits,bofstream&>
	operator<<(std::pair<Bits,bofstream&> p,int value)
	noexcept(false)
	{
		if(p.first.n==0)return p;
		
		if(p.first.n > 16){
			std::string message = "Over max bits size ";
			message += __func__;
			throw std::invalid_argument(message.c_str());
		}


		if(p.first.n > 8){
			p.second.write8bits(srook::byte(value >> 8),p.first.n - 8);
			p.first.n = 8;
		}
		p.second.write8bits(srook::byte(value),p.first.n);
		return p;
	}

	template<class Range>
	friend std::pair<const Byte_n&,bofstream&>
	operator<<(std::pair<const Byte_n&,bofstream&> p,const Range& r)
	noexcept(false)
	{
		if(p.second.forward_iter + p.first.n < p.second.last){
			p.second.set_fullbit();

			if constexpr(srook::has_iterator_v<std::decay_t<Range>>){
				std::memcpy(p.second.forward_iter,r.data(),p.first.n);
			}else{
				std::memcpy(p.second.forward_iter,r,p.first.n);
			}
			p.second.forward_iter += p.first.n;
		}else{
			throw std::runtime_error(__func__);
		}
		return p;
	}
	
	template<class Tag>
	constexpr friend std::pair<Tag,bofstream&> operator|(bofstream& ofps,const Tag& t)
	{	
		return std::make_pair(t,std::ref(ofps));
	}
	
	friend std::pair<Bits,bofstream&> operator|(bofstream& ofps,const Bits& bits)
	{
		return std::make_pair(bits,std::ref(ofps));
	}
};

} // inline namespace
} // namespace jpeg
} // namespace io
} // namespace srook
#endif
