#pragma once


#ifdef CALLA_EXPORTS
#define CALLA_API __declspec(dllexport)
#else
#define CALLA_API __declspec(dllimport)
#endif

extern "C" CALLA_API void load_asio_and_init(
    const unsigned long long a, const unsigned long long b);


extern "C" CALLA_API bool isConnectingExists();

extern "C" CALLA_API unsigned long long send_data();

extern "C" CALLA_API unsigned send_updates();

extern "C" CALLA_API void getReturnUpdatingMapTickL();

extern "C" CALLA_API void print_los_data(const char* name, int value);

extern "C" CALLA_API  void print_los_data_char(const char* name, const char* myMessage);

extern "C" CALLA_API  void load_connectionIs(static bool& isInternetConnectionExists);