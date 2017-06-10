
#include <stdlib.h>
#include <string.h>
#include "rest-engine.h"
#include "dev/tsl256x.h"
#include "AESMessage.h"

static int light;

static void res_get_handler(void *request, void *response, uint8_t *buffer, uint16_t preferred_size, int32_t *offset);

RESOURCE(res_getLight,
         "Get light",
         res_get_handler,
         NULL,
         NULL,
         NULL);

static void
res_get_handler(void *request, void *response, uint8_t *buffer, uint16_t preferred_size, int32_t *offset)
{ 
  SENSORS_ACTIVATE(tsl256x);
  light = tsl256x.value(TSL256X_VAL_READ);

  REST.set_header_content_type(response, REST.type.APPLICATION_JSON);
  
  snprintf((char *)buffer, REST_MAX_CHUNK_SIZE, 
	    "{\"Sensors\":{\"Light\":\"%02d\"}}",
             light);

  REST.set_response_payload(response, (uint8_t *)buffer, strlen((char *)buffer));
}
