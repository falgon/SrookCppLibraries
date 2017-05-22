#ifndef INCLUDED_SROOK_K_MEANS_HPP
#define INCLUDED_SROOK_K_MEANS_HPP

#include<iostream> 
#include<string_view>
#include<fstream>
#include<utility>
#include<stdexcept>
#include<vector>
#include<cstdio> 
#include<cmath>
#include<tuple>
#include<random>
#include<cassert>
#include<limits>
#include<srook/algorithm/for_each.hpp>

namespace srook{
namespace k_mns{

struct ploter{
	constexpr ploter(const char* file):file_(file){}
	
	void output(const char* plt_command)noexcept(false)
	{
		using namespace std::string_literals;

		std::FILE* fp=popen("gnuplot","w");
		if(fp==nullptr)throw std::runtime_error("could not start gnuplot properly");
		std::string file_type,plt_cmd=plt_command;
		plt_cmd+="\n";

		std::copy(std::next(std::begin(file_),file_.find(".")+1),std::end(file_),std::back_inserter(file_type));
		std::string first_cmd="set terminal "s+file_type+"\n"s;
		std::string second_cmd="set output \""s+std::string(file_.data())+"\"\n"s;

		std::fputs(first_cmd.c_str(),fp);
		std::fputs(second_cmd.c_str(),fp);
		std::fputs(plt_cmd.c_str(),fp);

		std::fflush(fp);
		pclose(fp);
	}
private:
	const std::string_view file_;
};

using Point=std::pair<double,double>;

struct k_means{
	k_means(const char* file,std::size_t clustering_size):master_vec(std::move(clustering_size)),initialized(false)
	{
		std::ifstream ifs(file);
		if(!ifs.fail()){
			std::string one_point,first,second;
			while(std::getline(ifs,one_point)){
				std::string::const_iterator iter=std::next(std::begin(one_point),one_point.find(","));
				std::copy(std::cbegin(one_point),iter,std::back_inserter(first));
				std::copy(std::next(iter,1),std::cend(one_point),std::back_inserter(second));

				input_data.emplace_back(Point{std::stod(first),std::stod(second)});
				first.clear();
				second.clear();
			}
		}
	}

	template<
		class... Ts,
		std::enable_if_t<(sizeof...(Ts)>0) and std::conjunction_v<std::is_same<Point,Ts>...>,std::nullptr_t> =nullptr
	>
	void set_initial_point(Ts&&... ts)noexcept
	{
		const std::tuple<std::decay_t<Ts>...> tpl{std::forward<Ts>(ts)...};
		assert(sizeof...(ts)==clustering_size());
		srook::for_each(srook::make_counter(tpl),[this](const auto& x,std::size_t i){master_vec[i]=x;});
		initialized=true;
	}

	template<class T>
	using rand_type=
		std::conditional_t<
			!std::is_same_v<std::decay_t<T>,double> and !std::is_same_v<std::decay_t<T>,float>,
			std::uniform_int_distribution<std::decay_t<T>>,
			std::uniform_real_distribution<std::decay_t<T>>
		>;
	template<class X,class Y>
	void set_initial_point(X&& x_min,X&& x_max,Y&& y_min,Y&& y_max)
	{
		std::random_device rd;
		std::mt19937 gen(rd());

		rand_type<X> x_dis(std::move(x_min),std::move(x_max));
		rand_type<Y> y_dis(std::move(y_min),std::move(y_max));
		
		for(auto& v:master_vec)
			v=Point{x_dis(gen),y_dis(gen)};
		initialized=true;
	}

	void clustering()
	{
		if(!initialized){
			std::vector<Point::first_type> xs(input_data.size());
			std::vector<Point::second_type> ys(input_data.size());
			srook::for_each(srook::make_counter(xs),[this](auto& x,std::size_t i){x=input_data[i].first;});
			srook::for_each(srook::make_counter(ys),[this](auto& y,std::size_t i){y=input_data[i].second;});
			
			set_initial_point(
					*std::min_element(std::begin(xs),std::end(xs)),*std::max_element(std::begin(xs),std::end(xs)),
					*std::min_element(std::begin(ys),std::end(ys)),*std::max_element(std::begin(ys),std::end(ys))
			);
		}

		std::vector<int> prev_cluster(input_data.size(),0);
		cluster.resize(input_data.size(),-1);

		while(!std::equal(std::begin(prev_cluster),std::end(prev_cluster),std::begin(cluster),std::end(cluster))){
			prev_cluster=cluster;

			srook::for_each(
					srook::make_counter(input_data),
					[this](const auto& v,std::size_t i)
					{
						int max_cluster=-1;
						double arg_max=std::numeric_limits<double>::infinity();

						srook::for_each(
								srook::make_counter(master_vec),
								[this,&arg_max,&v,&max_cluster](const auto& mp,std::size_t j)
								{
									if(arg_max > distance(v,mp)){
										arg_max=distance(v,mp);
										max_cluster=j;
									}
								}
						);
						cluster[i]=max_cluster;
					}
			);
			
			srook::for_each(
					srook::make_counter(master_vec),
					[this](auto& m,int i)
					{
						int c=0;
						m.first=0;
						m.second=0;
						srook::for_each(
								srook::make_counter(input_data),
								[i,&c,&m,this](const auto& v,std::size_t j)
								{
									if(cluster[j]==i){
										m.first+=v.first;
										m.second+=v.second;
										++c;
									}
								}
						);
						if(c){
							m.first/=c;
							m.second/=c;
						}
					}
			);
		}
	}

	std::vector<Point>::size_type clustering_size()const noexcept
	{
		return master_vec.size();
	}
private:
	std::vector<Point> input_data;
	std::vector<int> cluster;
	std::vector<Point> master_vec;
	bool initialized;
private:
	double distance(const Point& l,const Point& r)noexcept
	{
		return std::sqrt(std::pow(l.first-r.first,2.0) + std::pow(l.second-r.second,2.0));
	}

	friend std::ofstream& operator<<(std::ofstream& ofs,const k_means& km)
	{
		for(std::size_t i=0; i<km.clustering_size(); ++i){
			srook::for_each(
					srook::make_counter(km.input_data),
					[i,&ofs,&km](const auto& v,std::size_t j)
					{
						if(std::size_t(km.cluster[j])==i){
							ofs<<v.first<<" "<<v.second<<"\n";
						}
					}
			);
			ofs<<"\n\n";
		}
		return ofs;
	}

	friend std::ostream& operator<<(std::ostream& os,const k_means& km)
	{
		for(std::size_t i=0; i<km.clustering_size(); ++i){
			srook::for_each(
					srook::make_counter(km.input_data),
					[i,&os,&km](const auto& v,std::size_t j)
					{
						if(std::size_t(km.cluster[j])==i){
							os<<v.first<<","<<v.second<<"\n";
						}
					}
			);
			os<<"\n";
		}
		return os;
	}
};

} // namespace k_mns
} // namespace srook

#endif
