
#include <aerospike/as_config.h>
#include <aerospike/as_password.h>
#include <aerospike/as_policy.h>
#include <aerospike/as_string.h>
#include <aerospike/mod_lua_config.h>

#include <stdbool.h>
#include <stdint.h>

/******************************************************************************
 * MACROS
 *****************************************************************************/

#define MOD_LUA_CACHE_ENABLED false

/******************************************************************************
 * FUNCTIONS
 *****************************************************************************/

as_config * as_config_init(as_config * c) 
{
	c->ip_map = 0;
	c->ip_map_size = 0;
	c->max_threads = 300;
	c->max_socket_idle_sec = 14;
	c->conn_timeout_ms = 1000;
	c->tender_interval = 1000;
	c->hosts_size = 0;
	memset(c->user, 0, sizeof(c->user));
	memset(c->password, 0, sizeof(c->password));
	memset(c->hosts, 0, sizeof(c->hosts));
	as_policies_init(&c->policies);
	c->lua.cache_enabled = MOD_LUA_CACHE_ENABLED;
	strcpy(c->lua.system_path, AS_CONFIG_LUA_SYSTEM_PATH);
	strcpy(c->lua.user_path, AS_CONFIG_LUA_USER_PATH);
	c->fail_if_not_connected = false;
	return c;
}

bool
as_config_set_user(as_config* config, const char* user, const char* password)
{
	if (user && *user) {
		if (as_strncpy(config->user, user, sizeof(config->user))) {
			return false;
		}
		
		return as_password_get_constant_hash(password, config->password);
	}
	else {
		return false;
	}
}
