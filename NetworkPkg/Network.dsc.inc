## @file
# Network DSC include file for Platform DSC
#
# This file can be included to a platform DSC file by using "!include NetworkPkg/Network.dsc.inc".
#
# These flags can be defined before the !include line, or changed on the command
# line to enable or disable related feature support.
#   -D FLAG=VALUE
# The default value of these flags are:
#   DEFINE NETWORK_ENABLE                 = TRUE
#   DEFINE NETWORK_SNP_ENABLE             = TRUE
#   DEFINE NETWORK_IP4_ENABLE             = TRUE
#   DEFINE NETWORK_IP6_ENABLE             = TRUE
#   DEFINE NETWORK_TLS_ENABLE             = TRUE
#   DEFINE NETWORK_HTTP_BOOT_ENABLE       = TRUE
#   DEFINE NETWORK_ALLOW_HTTP_CONNECTIONS = FALSE
#   DEFINE NETWORK_IPSEC_ENABLE           = TRUE
#   DEFINE NETWORK_ISCSI_ENABLE           = TRUE
#   DEFINE NETWORK_VLAN_ENABLE            = TRUE
#
# Copyright (c) 2018, Intel Corporation. All rights reserved.<BR>
#
#    SPDX-License-Identifier: BSD-2-Clause-Patent
#
##

[Defines]
!ifndef NETWORK_ENABLE
  #
  # This flag is to enable or disable the whole network stack.
  #
  DEFINE NETWORK_ENABLE = TRUE
!endif

!ifndef NETWORK_SNP_ENABLE
  #
  # This flag is to include the common SNP driver or not.
  #
  DEFINE NETWORK_SNP_ENABLE = TRUE
!endif

!ifndef NETWORK_VLAN_ENABLE
  #
  # This flag is to enable or disable VLAN feature.
  #
  DEFINE NETWORK_VLAN_ENABLE = TRUE
!endif

!ifndef NETWORK_IP4_ENABLE
  #
  # This flag is to enable or disable IPv4 network stack.
  #
  DEFINE NETWORK_IP4_ENABLE = TRUE
!endif

!ifndef NETWORK_IP6_ENABLE
  #
  # This flag is to enable or disable IPv6 network stack.
  #
  DEFINE NETWORK_IP6_ENABLE = TRUE
!endif

!ifndef NETWORK_TLS_ENABLE
  #
  # This flag is to enable or disable TLS feature.
  #
  # Note: This feature depends on the OpenSSL building. To enable this feature, please
  #       follow the instructions found in the file "OpenSSL-HOWTO.txt" located in
  #       CryptoPkg\Library\OpensslLib to enable the OpenSSL building first.
  #       The OpensslLib.inf library instance should be used since libssl is required.
  #
  DEFINE NETWORK_TLS_ENABLE = TRUE
!endif

!ifndef NETWORK_HTTP_BOOT_ENABLE
  #
  # This flag is to enable or disable HTTP(S) boot feature.
  #
  DEFINE NETWORK_HTTP_BOOT_ENABLE = TRUE
!endif

!ifndef NETWORK_ALLOW_HTTP_CONNECTIONS
  #
  # Indicates whether HTTP connections (i.e., unsecured) are permitted or not.
  #
  # Note: If NETWORK_ALLOW_HTTP_CONNECTIONS is TRUE, HTTP connections are allowed.
  #       Both the "https://" and "http://" URI schemes are permitted. Otherwise, HTTP
  #       connections are denied. Only the "https://" URI scheme is permitted.
  #
  DEFINE NETWORK_ALLOW_HTTP_CONNECTIONS = FALSE
!endif

!ifndef NETWORK_ISCSI_ENABLE
  #
  # This flag is to enable or disable iSCSI feature.
  #
  # Note: This feature depends on the OpenSSL building. To enable this feature, please
  #       follow the instructions found in the file "OpenSSL-HOWTO.txt" located in
  #       CryptoPkg\Library\OpensslLib to enable the OpenSSL building first.
  #       Both OpensslLib.inf and OpensslLibCrypto.inf library instance can be used
  #       since libssl is not required for iSCSI.
  #
  DEFINE NETWORK_ISCSI_ENABLE = TRUE
!endif

!if $(NETWORK_ENABLE) == TRUE
  #
  # Check the flags to see if there is any conflict.
  #
  !if ($(NETWORK_IP4_ENABLE) == FALSE) AND ($(NETWORK_IP6_ENABLE) == FALSE)
    !error "Must enable at least IP4 or IP6 stack if NETWORK_ENABLE is set to TRUE!"
  !endif

  !if ($(NETWORK_HTTP_BOOT_ENABLE) == TRUE) AND ($(NETWORK_TLS_ENABLE) == FALSE) AND ($(NETWORK_ALLOW_HTTP_CONNECTIONS) == FALSE)
    !error "Must enable TLS to support HTTPS, or allow unsecured HTTP connection, if NETWORK_HTTP_BOOT_ENABLE is set to TRUE!"
  !endif
!endif

[PcdsFixedAtBuild]
!if $(NETWORK_ALLOW_HTTP_CONNECTIONS) == TRUE
  gEfiNetworkPkgTokenSpaceGuid.PcdAllowHttpConnections|TRUE
!endif

[LibraryClasses]
  DpcLib|NetworkPkg/Library/DxeDpcLib/DxeDpcLib.inf
  NetLib|NetworkPkg/Library/DxeNetLib/DxeNetLib.inf
  IpIoLib|NetworkPkg/Library/DxeIpIoLib/DxeIpIoLib.inf
  UdpIoLib|NetworkPkg/Library/DxeUdpIoLib/DxeUdpIoLib.inf
  TcpIoLib|NetworkPkg/Library/DxeTcpIoLib/DxeTcpIoLib.inf
  HttpLib|NetworkPkg/Library/DxeHttpLib/DxeHttpLib.inf

[Components]

!if $(NETWORK_ENABLE) == TRUE
  NetworkPkg/DpcDxe/DpcDxe.inf

  !if $(NETWORK_SNP_ENABLE) == TRUE
    NetworkPkg/SnpDxe/SnpDxe.inf
  !endif

  !if $(NETWORK_VLAN_ENABLE) == TRUE
    NetworkPkg/VlanConfigDxe/VlanConfigDxe.inf
  !endif

  NetworkPkg/MnpDxe/MnpDxe.inf

  !if $(NETWORK_IP4_ENABLE) == TRUE
    NetworkPkg/ArpDxe/ArpDxe.inf
    NetworkPkg/Dhcp4Dxe/Dhcp4Dxe.inf
    NetworkPkg/Ip4Dxe/Ip4Dxe.inf
    NetworkPkg/Udp4Dxe/Udp4Dxe.inf
    NetworkPkg/Mtftp4Dxe/Mtftp4Dxe.inf
  !endif

  !if $(NETWORK_IP6_ENABLE) == TRUE
    NetworkPkg/Dhcp6Dxe/Dhcp6Dxe.inf
    NetworkPkg/Ip6Dxe/Ip6Dxe.inf
    NetworkPkg/Udp6Dxe/Udp6Dxe.inf
    NetworkPkg/Mtftp6Dxe/Mtftp6Dxe.inf
  !endif

  NetworkPkg/TcpDxe/TcpDxe.inf
  NetworkPkg/UefiPxeBcDxe/UefiPxeBcDxe.inf

  !if $(NETWORK_TLS_ENABLE) == TRUE
    NetworkPkg/TlsDxe/TlsDxe.inf
    NetworkPkg/TlsAuthConfigDxe/TlsAuthConfigDxe.inf
  !endif

  !if $(NETWORK_HTTP_BOOT_ENABLE) == TRUE
    NetworkPkg/DnsDxe/DnsDxe.inf
    NetworkPkg/HttpDxe/HttpDxe.inf
    NetworkPkg/HttpUtilitiesDxe/HttpUtilitiesDxe.inf
    NetworkPkg/HttpBootDxe/HttpBootDxe.inf
  !endif

  !if $(NETWORK_ISCSI_ENABLE) == TRUE
    NetworkPkg/IScsiDxe/IScsiDxe.inf
  !endif
!endif
