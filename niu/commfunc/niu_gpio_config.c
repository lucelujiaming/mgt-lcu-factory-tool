#include "niu_cmd.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>
#include "niu_gpio_config.h"

extern gpio_bcm_config g_niu_raspberrypi_gpio_config[30] = {
        {17, IN  } /* GPIO  0 */,  {18, IN  }  /* GPIO  1 */,  { 27, IN  }  /* GPIO  2 */,
        {22, IN  } /* GPIO  3 */,  {23, IN  }  /* GPIO  4 */,  { 24, IN  }  /* GPIO  5 */,
        {25, IN  } /* GPIO  6 */,  { 4, IN  }   /* GPIO  7 */, { -1, NO  }  /* GPIO  8 */,
        {-1, NO  } /* GPIO  9 */,  {-1, NO  }  /* GPIO 10 */,  { -1, NO  }  /* GPIO 11 */,
        {-1, NO  } /* GPIO 12 */,  {-1, NO  }  /* GPIO 13 */,  { -1, NO  }  /* GPIO 14 */,
        {-1, NO  } /* GPIO 15 */,  {-1, NO  }  /* GPIO 16 */,  { -1, NO  }  /* GPIO 17 */,
        {-1, NO  } /* GPIO 18 */,  {-1, NO  }  /* GPIO 19 */,  { -1, NO  }  /* GPIO 20 */,
        { 5, KEY } /* GPIO 21 */,  { 6, OUT }  /* GPIO 22 */,  { 13, OUT }  /* GPIO 23 */,
        {19, OUT } /* GPIO 24 */,  {26, OUT }  /* GPIO 25 */,  { 12, OUT }  /* GPIO 26 */,
        {16, OUT } /* GPIO 27 */,  {20, OUT }  /* GPIO 28 */,  { 21, OUT }  /* GPIO 29 */
};

