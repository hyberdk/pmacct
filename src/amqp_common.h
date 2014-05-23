/*
    pmacct (Promiscuous mode IP Accounting package)
    pmacct is Copyright (C) 2003-2014 by Paolo Lucente
*/

/*
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
*/

/* includes */
#include <amqp.h>
#include <amqp_tcp_socket.h>

/* defines */
#define AMQP_PUBLISH_MSG	1
#define AMQP_PUBLISH_LOG	2

/* structures */
struct p_amqp_host {
  char *user;
  char *passwd;
  char *exchange;
  char *exchange_type;
  char *routing_key;
  char *host;
  int persistent_msg;

  amqp_connection_state_t conn;
  amqp_socket_t *socket;
  amqp_rpc_reply_t ret;
  struct amqp_basic_properties_t_ msg_props;
  int status;
};

/* prototypes */
#if (!defined __AMQP_COMMON_C)
#define EXT extern
#else
#define EXT
#endif

EXT void p_amqp_init_host(struct p_amqp_host *);
EXT void p_amqp_set_user(struct p_amqp_host *, char *);
EXT void p_amqp_set_passwd(struct p_amqp_host *, char *);
EXT void p_amqp_set_exchange(struct p_amqp_host *, char *);
EXT void p_amqp_set_routing_key(struct p_amqp_host *, char *);
EXT void p_amqp_set_exchange_type(struct p_amqp_host *, char *);
EXT void p_amqp_set_host(struct p_amqp_host *, char *);
EXT void p_amqp_set_persistent_msg(struct p_amqp_host *, int);

EXT int p_amqp_connect(struct p_amqp_host *, int);
EXT int p_amqp_publish(struct p_amqp_host *, char *, int);
EXT void p_amqp_close(struct p_amqp_host *, int);

/* global vars */
EXT struct p_amqp_host amqpp_amqp_host, log_amqp_host;

static char rabbitmq_user[] = "guest";
static char rabbitmq_pwd[] = "guest";
static char default_amqp_exchange[] = "pmacct";
static char default_amqp_exchange_type[] = "direct";
static char default_amqp_routing_key[] = "acct";
static char default_amqp_host[] = "127.0.0.1";
#undef EXT
