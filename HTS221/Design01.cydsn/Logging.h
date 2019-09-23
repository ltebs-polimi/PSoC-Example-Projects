/**
*   \file Logging.h
*
*   This driver allows to log data for debug purposes.
*   Here you can find all the macros and function
*   declarations that can be used for debug purposes.
*
*   \author Davide Marzorati
*   \date September 23, 2019
*/


#ifndef __LOGGING_H
    #define __LOGGING_H
    
    #include "HTS221.h"
    #include "Logging_Interface.h"
    
    /**
    *   \brief Macro to enable debug messages.
    *
    *   If you want to disable debug messages, comment this out.
    */
    #ifndef DEBUG_ENABLED
        #define DEBUG_ENABLED
    #endif
        

    
    /**
    *   \brief Welcome string
    */
    #ifndef WELCOME_STRING
        #define WELCOME_STRING "\n************************\n* HTS221 Program Start *\n************************\n"
    #endif
    
    /**
    *   \brief Warning string for debug enabled
    */
    #ifndef DEBUG_ENABLED_STRING
        #define DEBUG_ENABLED_STRING "Warning: Debug is enabled.\n"
    #endif
    
    LoggingError Logging_Start(void);

    LoggingError Logging_Stop(void);
    
    LoggingError Logging_PrintHTS221Configuration(HTS221_Struct* hts221);
    
    #endif
/* [] END OF FILE */
