
/* * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 *      Copyright (c) 2014 Jenson Sze.
 *          http://shixf.com/
 *
 *          Keyboard Hook API
 *
 *                      by Jenson
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * */


#ifndef __JSNSZE_HOOK_H__
#define __JSNSZE_HOOK_H__

#ifdef __cplusplus
extern "C" {
#endif


    #ifdef HOOK_EXPORTS
        #define JS_API                         __declspec(dllexport)
    #else
        #define JS_API                         __declspec(dllimport)
    #endif  /* HOOK_EXPORTS */


    /* Init Keyboard Hook */
    JS_API void KeyHookInit();


    /* Fini Keyboard Hook */
    JS_API void KeyHookCleanup();


#ifdef __cplusplus
}   /* extern "C" */
#endif

#endif  /* __JSNSZE_HOOK_H__ */
