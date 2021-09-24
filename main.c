/*
 * Copyright (C) 2021 Otto-von-Guericke-Universität Magdeburg
 */

/**
 * @defgroup
 * @ingroup
 * @brief
 * @{
 *
 * @file
 * @brief
 *
 * @author  Frank Engelhardt <fengelha@ovgu.de>
 */

#include <stdio.h>
#include <shell.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "net/gcoap.h"
#include "net/cord/ep.h"

#include "doriot_dca.h"
#include "msg.h"

#define MAIN_QUEUE_SIZE     (8)
static msg_t _main_msg_queue[MAIN_QUEUE_SIZE];

static const shell_command_t shell_commands[] = {
    { NULL, NULL, NULL }
};

static void _register_ep_in_rd(const char* addrstr, uint16_t port) {
    sock_udp_ep_t remote;
    ipv6_addr_t addr;
    remote.family = AF_INET6;
    remote.netif = SOCK_ADDR_ANY_NETIF;
    if (ipv6_addr_from_str(&addr, addrstr) == NULL) {
        puts("unable to parse RD address");
    }
    memcpy(remote.addr.ipv6, &addr.u8[0], sizeof(addr.u8));
    remote.port = port;

    int r = cord_ep_register(&remote, NULL);
    if(r == CORD_EP_OK) {
        puts("EP registration successful");
    }
    else if(r == CORD_EP_NORD) {
        puts("EP registration failed: no RD");
    }
    else if(r == CORD_EP_ERR) {
        puts("EP registration failed: communication failure to RD");
    }
}

int main(void)
{
    /* required for network statistics */
#ifdef CONFIG_DCA_NETWORK
    db_start_udp_server();
#endif /* CONFIG_DCA_NETWORK */
    db_coap_init();

    /*xtimer_sleep(1);*/
    _register_ep_in_rd(CONFIG_RD_ADDR, CONFIG_RD_PORT);

    msg_init_queue(_main_msg_queue, MAIN_QUEUE_SIZE);
    char line_buf[SHELL_DEFAULT_BUFSIZE];

    shell_run(shell_commands, line_buf, SHELL_DEFAULT_BUFSIZE);
    return 0;
}
