// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CONFIG_ENVIRONMENT_OS_LINUX_NET_IF_ETHER_HPP
#define INCLUDED_SROOK_CONFIG_ENVIRONMENT_OS_LINUX_NET_IF_ETHER_HPP

#ifdef __linux__

#ifndef _LINUX_IF_ETHER_H
#   include <linux/if_ether.h>
#endif

#include <srook/config/feature/nested_namespace.hpp>
#include <srook/config/feature/inline_namespace.hpp>
#include <srook/config/feature/inline_variable.hpp>
#include <srook/config/feature/constexpr.hpp>
#include <srook/config/feature/strong_enum.hpp>
#include <srook/cstdint.hpp>

SROOK_NESTED_NAMESPACE(srook, environment, linux) {
SROOK_INLINE_NAMESPACE(v1)

struct info;
struct protocol;

struct ethernet_traits {
#define SROOK_DECL_STATIC_CONS static SROOK_INLINE_VARIABLE SROOK_CONSTEXPR_OR_CONST
    typedef std::size_t size_type;
    SROOK_DECL_STATIC_CONS size_type addr_size = ETH_ALEN;
    SROOK_DECL_STATIC_CONS size_type oct_head_size = ETH_HLEN;
    SROOK_DECL_STATIC_CONS size_type oct_frame_min = ETH_ZLEN;
    SROOK_DECL_STATIC_CONS size_type oct_data_max = ETH_DATA_LEN;
    SROOK_DECL_STATIC_CONS size_type oct_frame_max = ETH_FRAME_LEN;
    SROOK_DECL_STATIC_CONS size_type oct_fcs_size = ETH_FCS_LEN;
    SROOK_DECL_STATIC_CONS size_type mtu_min = ETH_MIN_MTU;
    SROOK_DECL_STATIC_CONS size_type mtu_max = ETH_MAX_MTU;
    
    SROOK_STRONG_ENUM_BEGIN (protocols) {
        loop = ETH_P_LOOP,
        pup =  ETH_P_PUP,
        pupat = ETH_P_PUPAT,
        tsn = ETH_P_TSN,
        ip = ETH_P_IP,
        x25 = ETH_P_X25,
        arp = ETH_P_ARP,
        bpq = ETH_P_BPQ,
        ieeepup = ETH_P_IEEEPUP,
        ieeepupat = ETH_P_IEEEPUPAT,
        batman = ETH_P_BATMAN,
        dec = ETH_P_DEC,
        dna_dl = ETH_P_DNA_DL,
        dna_rc = ETH_P_DNA_RC,
        dna_rt = ETH_P_DNA_RT,
        lat = ETH_P_LAT,
        diag = ETH_P_DIAG,
        cust = ETH_P_CUST,
        sca = ETH_P_SCA,
        teb = ETH_P_TEB,
        rarp = ETH_P_RARP,
        atalk = ETH_P_ATALK,
        aarp = ETH_P_AARP,
        q8021 = ETH_P_8021Q,
        ipx = ETH_P_IPX,
        ipv6 = ETH_P_IPV6,
        pause = ETH_P_PAUSE,
        slow = ETH_P_SLOW,
        wccp = ETH_P_WCCP,
        mpls_uc = ETH_P_MPLS_UC,
        mpls_mc = ETH_P_MPLS_MC,
        atmmpoa = ETH_P_ATMMPOA,
        ppp_disc = ETH_P_PPP_DISC,
        ppp_ses = ETH_P_PPP_SES,
        link_ctl = ETH_P_LINK_CTL,
        atm_fate = ETH_P_ATMFATE,
        pae = ETH_P_PAE,
        aoe = ETH_P_AOE,
        ad8021 = ETH_P_8021AD,
        ex1_802 = ETH_P_802_EX1,
        tipc = ETH_P_TIPC,
        macsec = ETH_P_MACSEC,
        ah8021 = ETH_P_8021AH,
        mvrp = ETH_P_MVRP,
        ieee1588 = ETH_P_1588,
        ncsi = ETH_P_NCSI,
        prp = ETH_P_PRP,
        fcoe = ETH_P_FCOE,
        iboe = ETH_P_IBOE,
        tdls = ETH_P_TDLS,
        fip = ETH_P_FIP,
        ieee80221 = ETH_P_80221,
        hsr = ETH_P_HSR,
        ieee802_3_loopback = ETH_P_LOOPBACK,
        qinq1 = ETH_P_QINQ1,
        qinq2 = ETH_P_QINQ2,
        qinq3 = ETH_P_QINQ3,
        edsa = ETH_P_EDSA,
        af_iucv = ETH_P_AF_IUCV,
        all = ETH_P_ALL,
        frame_802_2 = ETH_P_802_2,
        snap = ETH_P_SNAP,
        ddcmp = ETH_P_DDCMP,
        wan_ppp = ETH_P_WAN_PPP,
        ppp_mp = ETH_P_PPP_MP,
        localtalk = ETH_P_LOCALTALK,
        can = ETH_P_CAN,
        canfd = ETH_P_CANFD,
        ppptalk = ETH_P_PPPTALK,
        tr802_2 = ETH_P_TR_802_2,
        mobitex = ETH_P_MOBITEX,
        control = ETH_P_CONTROL,
        irda = ETH_P_IRDA,
        econet = ETH_P_ECONET,
        hdlc = ETH_P_HDLC,
        arcnet = ETH_P_ARCNET,
        dsa = ETH_P_DSA,
        trailer = ETH_P_TRAILER,
        phonet = ETH_P_PHONET,
        ieee802154 = ETH_P_IEEE802154,
        caif = ETH_P_CAIF,
        xdsa = ETH_P_XDSA
    };
    SROOK_STRONG_ENUM_EPILOG(protocols)
        
    srook::uint16_t p802_3_min = ETH_P_802_3_MIN;
};

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(linux, environment, srook)

#undef SROOK_DECL_STATIC_CONS
#endif
#endif
