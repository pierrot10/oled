#include <stdio.h>

// For OLED LCD
#include "ArduiPi_OLED_lib.h"
#include "Adafruit_GFX.h"
#include "ArduiPi_OLED.h"

#include <getopt.h>

#define PRG_NAME        "welcome"
#define PRG_VERSION     "1.1"

// Instantiate the display
ArduiPi_OLED display;

// Config Option
struct s_opts
{
        int oled;
        int verbose;
} ;

int sleep_divisor = 1 ;
        
// default options values
s_opts opts = {
        OLED_ADAFRUIT_I2C_128x32,       // Default oled
  false                                 // Not verbose
};


void usage( char * name)
{
        printf("%s\n", name );
        printf("Usage is: %s --oled type [options]\n", name);
        printf("  --<o>led type\nOLED type are:\n");
        for (int i=0; i<OLED_LAST_OLED;i++)
                printf("  %1d %s\n", i, oled_type_str[i]);
                                                
        printf("Options are:\n");
        printf("  --<v>erbose  : speak more to user\n");
        printf("  --<h>elp\n");
        printf("<?> indicates the equivalent short option.\n");
        printf("Short options are prefixed by \"-\" instead of by \"--\".\n");
        printf("Example :\n");
        printf( "%s -o 1 use a %s OLED\n\n", name, oled_type_str[1]);
        printf( "%s -o 4 -v use a %s OLED being verbose\n", name, oled_type_str[4]);
}

void parse_args(int argc, char *argv[])
{
        static struct option longOptions[] =
        {
                {"oled"   , required_argument,0, 'o'},
                {"verbose", no_argument,                0, 'v'},
                {"help"         , no_argument,                  0, 'h'},
                {0, 0, 0, 0}
        };

        int optionIndex = 0;
        int c;

        while (1) 
        {
                /* no default error messages printed. */
                opterr = 0;

                c = getopt_long(argc, argv, "vho:", longOptions, &optionIndex);

                if (c < 0)
                        break;

                switch (c) 
                {
                        case 'v': opts.verbose = true   ;       break;
                        
                        case 'o':
                                opts.oled = (int) atoi(optarg);
                                
                                if (opts.oled < 0 || opts.oled >= OLED_LAST_OLED )
                                {
                                                fprintf(stderr, "--oled %d ignored must be 0 to %d.\n", opts.oled, OLED_LAST_OLED-1);
                                                fprintf(stderr, "--oled set to 0 now\n");
                                                opts.oled = 0;
                                }
                        break;
                        
                        case 'h':
                                usage(argv[0]);
                                exit(EXIT_SUCCESS);
                        break;
                        
                        case '?':
                        default:
                                fprintf(stderr, "Unrecognized option.\n");
                                fprintf(stderr, "Run with '--help'.\n");
                                exit(EXIT_FAILURE);
                }
        } /* while */
        if (opts.verbose)
        {
                printf("%s v%s\n", PRG_NAME, PRG_VERSION);
                printf("-- OLED params -- \n");
                printf("Oled is    : %s\n", oled_type_str[opts.oled]);
                printf("-- Other Stuff -- \n");
                printf("verbose is : %s\n", opts.verbose? "yes" : "no");
                printf("\n");
        }       
}


int main(int argc, char **argv)
{
        parse_args(argc, argv);
        // I2C change parameters to fit to your LCD
        if ( !display.init(OLED_I2C_RESET,opts.oled) )
        {
                exit(EXIT_FAILURE);
        };
        display.begin();
  
        printf("Hello, World! \n");
        display.clearDisplay();   // clears the screen  buffer
        
              // text display tests
        display.setTextSize(1);
        display.setTextColor(WHITE);
        display.setCursor(0,0);
        display.print("Welcome aboard\n");
        display.setTextColor(BLACK, WHITE); // 'inverted' text
        display.setTextSize(2);
        display.print("SmartIdea\n");
        display.setTextSize(1);
        display.setTextColor(WHITE);
        display.print("smart-idea.io");
        display.display();
        sleep(3); 
        return 0;
}
