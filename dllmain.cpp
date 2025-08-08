// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "CallA.h"


#include <asio.hpp>
#include <asio/ts/buffer.hpp>
#include <asio/ts/internet.hpp>

#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>


//#define ASIO_STANDALONE
//#define BOOST_ASIO_NO_WIN32_LEAN_AND_MEAN
//#define BOOST_ASIO_SEPARATE_COMPILATION
//#define BOOST_ASIO_DISABLE_VISIBILITY
//#define BOOST_ASIO_HAS_CLANG_LIBCXX

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}



bool RedirectConsoleIO();
bool ReleaseConsole();
void AdjustConsoleBuffer(int16_t minLength);
void CreateNewConsole(int16_t minLength);
bool AttachParentConsole(int16_t minLength);
void print_los_data(const char* name, int value);
void print_los_data_char(const char* name, const char* myMessage);
void load_connectionIs(static bool& isInternetConnectionExists); // static ?

static unsigned long long previous_;  // Previous value, if any
static unsigned long long current_;   // Current sequence value
static unsigned index_;               // Current seq. position


//constexpr const std::string sRequest1 =
//"GET /get_return_updating_map_new_tick_start HTTP/1.1\r\n"
//"Host: losbalderdash.com\r\n"
//"Connection: close\r\n\r\n";



std::vector<char> vBuffer(1 * 1024);
void GrabSomeData(asio::ip::tcp::socket& socket)
{
    socket.async_read_some(asio::buffer(vBuffer.data(), vBuffer.size()),
        [&](std::error_code ec, std::size_t length)
        {
            if (!ec)
            {
                //std::cout << "\n\n Read " << length << " bytes \n\n";

                for (int i = 0; i < length; i++)
                    //   std::cout << vBuffer[i];

                    GrabSomeData(socket);
            }
        }

    );
}



class myAsio
{
public:
    
    myAsio() {


        std::cout << "Start constructor ! " << "\n";
       
        //asio::ip::tcp::endpoint endpoint(asio::ip::make_address("34.51.147.110:8000", ec), 80);
        //asio::ip::tcp::socket socket(context);
		//socket = asio::ip::tcp::socket(context);

       // socket.connect(endpoint, ec);


        std::cout << " print a " << " \n";
        unsigned int n = std::thread::hardware_concurrency();
        std::cout << n << " concurrent threads are supported.\n";


    }


    void sendInitialData() {


        asio::error_code ec;
        asio::io_context context;


        asio::io_context::work idleWork(context); // fake taskt to asi so the context does'n finish 
        std::thread thrContext = std::thread([&]() { context.run();  });

        //   C++   losBalderdash.com     ip 84.201.148.195          nginx 1.16.1

        asio::ip::tcp::endpoint endpoint(asio::ip::make_address("34.51.147.110:8000", ec), 80);
        asio::ip::tcp::socket socket(context);


        socket.connect(endpoint, ec);




        if (!ec) {
            std::cout << "Connected ! " << "\n";
        }
        else {
            std::cout << " Failed to connect to address : " << ec.message() << "\n";
        }


        if (socket.is_open()) {
            GrabSomeData(socket);


            std::string sRequest =
                "GET /ehi?baton=los_oksd&dev_castle=102 HTTP/1.1\r\n"
                "Host: losbalderdash.com\r\n"
                "Connection: close\r\n\r\n";

            socket.write_some(asio::buffer(sRequest.data(), sRequest.size()), ec);

        }





        // myAsioInstance = new myAsio();
        // std::this_thread::sleep_for(std::chrono::seconds(1));




        std::this_thread::sleep_for(std::chrono::seconds(2));
        GrabSomeData(socket);

        context.stop();


        if (thrContext.joinable()) {

            thrContext.join();

            std::cout << "if we are finished - close  " << " \n";


            socket.close();

        }




    /*    asio::io_context::work idleWork(context);
        asio::ip::tcp::endpoint endpoint(asio::ip::make_address("34.51.147.110:8000", ec), 80);
        asio::ip::tcp::socket socket(context);
        std::thread thrContext = std::thread([&]() { context.run();  });

        std::cout << "Send initial data " << "\n";


        socket.connect(endpoint, ec);


        if (!ec) {
            std::cout << "Connected ! " << "\n";
        }
        else {
            std::cout << " Failed to connect to address : " << ec.message() << "\n";
        }



        if (socket.is_open()) {
			std::cout << "Socket is open ! (initial) " << "\n";
            GrabSomeData(socket);


            std::string sRequest =
                "GET /ehi?baton=los_oksd&dev_castle=102 HTTP/1.1\r\n"
                "Host: losbalderdash.com\r\n"
                "Connection: close\r\n\r\n";

            socket.write_some(asio::buffer(sRequest.data(), sRequest.size()), ec);

            socket.close();
        }

        std::this_thread::sleep_for(std::chrono::seconds(2));
          GrabSomeData(socket);

          context.stop();


                if (thrContext.joinable()) {

             thrContext.join();

             std::cout << "if we are finished - close  " << " \n";


             socket.close();

         }*/


    }


    std::string gen_random(const int len) {
        static const char alphanum[] =
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";
        std::string tmp_s;
        tmp_s.reserve(len);

        for (int i = 0; i < len; ++i) {
            tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
        }

        return tmp_s;
    }


    void sendUpdateMap() {


        asio::error_code ec;
        asio::io_context context;


        asio::io_context::work idleWork(context); // fake taskt to asi so the context does'n finish 
        std::thread thrContext = std::thread([&]() { context.run();  });

        //   C++   losBalderdash.com     ip 84.201.148.195          nginx 1.16.1

        asio::ip::tcp::endpoint endpoint(asio::ip::make_address("34.51.147.110:8000", ec), 80);
        asio::ip::tcp::socket socket(context);


        socket.connect(endpoint, ec);




        if (!ec) {
            std::cout << "Connected ! " << "\n";
        }
        else {
            std::cout << " Failed to connect to address : " << ec.message() << "\n";
        }

        std::cout << " pre send POST " << " \n";

        if (socket.is_open()) {
            GrabSomeData(socket);


            std::vector<char> buffer(8);

            asio::streambuf requesrA;
            
            //std::ostream requestStream(&requesrA);
            std::ostringstream requestStream;


            std::string sRequest =
                "POST /send_update_map HTTP/1.1\r\n" // was GET
                "Host: losbalderdash.com\r\n"
                "Accept: */*\r\n"
                "Content-Length: 32\r\n"
                "Content-Type: application/x-www-form-urlencoded"
                "Connection: close\r\n\r\n";


            std::cout << " pre send POST 22 " << " \n";

            std::string sToSend = "msg=testing";

            int myInt = 12345;
            float myFloat = 3.14159f;

            //            Write myInt to the beginning of the buffer
            std::memcpy(buffer.data(), &myInt, sizeof(myInt));

			std::cout << " my size = " << buffer.size() << " \n";
            // requestStream <<  "Content-Type: application/x-www-form-urlencoded"; was and work
            // "Content-Type: multipart/form-data";



            std::cout << " pre send POST 23 " << " \n";
            // Content-Type: application/multipart/form-data
            requestStream << "POST /send_update_map HTTP/1.1\r\n";
            requestStream << "Host: losbalderdash.com\r\n";
			//requestStream << "User - Agent: Boost.Asio Client\r\n";
            // requestStream << "Accept: */*\r\n";
            requestStream << "Content-Type: application/octet-stream\r\n";
            requestStream << "Content-Length: " << buffer.size() << "\r\n";
            requestStream << "Connection: close\r\n\r\n";  // was close 
           // requestStream << buffer.data();

            //std::cout << " df " << requesrA << " \n";

            std::cout << " pre send POST 24 " << " \n";


            // A byte buffer of 8 bytes

            // Writing an int (4 bytes) and a float (4 bytes)


            // Write myFloat after myInt
           // std::memcpy(buffer.data() + sizeof(sRequest), &myFloat, sizeof(myFloat));

             // socket.write_some(asio::buffer(sRequest.data(), sRequest.size()), ec);
           // socket.write_some(asio::buffer(buffer.data(), buffer.size()), ec);

            std::string headers = requestStream.str();
            std::cout << " what a send to server == " << headers << " \n";
            std::vector<asio::const_buffer> buffers;
            buffers.push_back(asio::buffer(headers));
            buffers.push_back(asio::buffer(buffer));

            std::cout << " pre send POST 25 " << " \n";
           
            //asio::write(socket, buffers);

            socket.write_some(asio::buffer(buffers), ec);
            //socket.write_some(asio::buffer(requesrA.data(), requesrA.size()), ec); // ok work ! 
           // socket.write_some(asio::buffer(buffer.data(), buffer.size()), ec); // ok work !
        

           // asio::streambuf response;
           // asio::read_until(socket, response, "\r\n\r\n");

            // Process response headers (optional)
          /*  std::istream response_stream(&response);
            std::string http_version;
            response_stream >> http_version;
            unsigned int status_code;
            response_stream >> status_code;
            std::string status_message;
            std::getline(response_stream, status_message);

            std::cout << "Status LOS Code: " << status_code << std::endl;*/

           // socket.async_write_some(requesrA, ec);


            //std::ifstream inputFileStream;
            //inputFileStream.open("save\\map1.hot", std::ios::in | std::ios::binary);

            //if (inputFileStream.is_open()) {

            //    inputFileStream.seekg(0, std::ios::end);
            //    std::streampos fileSize = inputFileStream.tellg();
            //    inputFileStream.seekg(0, std::ios::beg);

            //    std::cout << " my size binary  " << fileSize << " \n";

            //    std::vector<char> buffer(fileSize); // Use a vector as a dynamic buffer
            //    inputFileStream.read(buffer.data(), fileSize);
            //    inputFileStream.close();

            //    std::vector<char> aBuf(8);
            //    
            //    int myInt = 12345;
            //   // std::memcpy(aBuf.data() + sizeof(), &myFloat, sizeof(myFloat));
            //    std::memcpy(aBuf.data(), &myInt, sizeof(myInt));

            //    std::string boundary = "---------------------------" + aBound; // Implement random string generation
            //    std::string body;

            //    // Add a file part
            //    body += "--" + boundary + "\r\n";
            //    body += "Content-Disposition: form-data; name=\"file\"; filename=\"map1.hot\"\r\n";
            //    body += "Content-Type: application/octet-stream\r\n";
            //    body += "\r\n";
            //    body.append(aBuf.begin(), aBuf.end()); // Append your binary data
            //    body += "\r\n";

            //    // Add other form fields if needed

            //    body += "--" + boundary + "--\r\n";

            //    std::string request_headers;
            //    request_headers += "POST /send_update_map HTTP/1.1\r\n";
            //    request_headers += "Host: losbalderdash.com\r\n";
            //    request_headers += "Content-Type: multipart/form-data; boundary=" + boundary + "\r\n";
            //    request_headers += "Content-Length: " + std::to_string(body.length()) + "\r\n";
            //    request_headers += "\r\n"; // End of headers

            //    // Combine headers and body
            //    std::vector<asio::const_buffer> buffers;
            //    buffers.push_back(asio::buffer(request_headers));
            //    buffers.push_back(asio::buffer(body));

            //    socket.write_some(asio::buffer(buffers.data(), buffers.size()), ec);


            //    if (!ec) {
            //        std::cout << "ok send data 12 ! " << "\n";
            //    }
            //    else {
            //        std::cout << " Failed to connect to address : " << ec.message() << "\n";
            //    }

            //}

            //// myAsioInstance = new myAsio();
            //// std::this_thread::sleep_for(std::chrono::seconds(1));

            //std::this_thread::sleep_for(std::chrono::seconds(2));
            //GrabSomeData(socket);

            //context.stop();


            //if (thrContext.joinable()) {

            //    thrContext.join();

            //    std::cout << "if we are finished update MAP - close  " << " \n";


            //    socket.close();

            //}


            //}
            //else {

            //}
            //   

           }

           std::this_thread::sleep_for(std::chrono::seconds(2));
           GrabSomeData(socket);

           context.stop();


           if (thrContext.joinable()) {

               thrContext.join();

               std::cout << "if we are finished - close  " << " \n";


               socket.close();

           }
    }


    void GetReturnUpdatingMapTick() {


            asio::error_code ec;
            asio::io_context context;


            asio::io_context::work idleWork(context); // fake taskt to asi so the context does'n finish 
            std::thread thrContext = std::thread([&]() { context.run();  });

            //   C++   losBalderdash.com     ip 84.201.148.195          nginx 1.16.1

            asio::ip::tcp::endpoint endpoint(asio::ip::make_address("34.51.147.110:8000", ec), 80);
            asio::ip::tcp::socket socket(context);


            socket.connect(endpoint, ec);




            if (!ec) {
                std::cout << "Connected ! " << "\n";
            }
            else {
                std::cout << " Failed to connect to address : " << ec.message() << "\n";
            }


            if (socket.is_open()) {
                GrabSomeData(socket);


                std::string sRequest =
                    "GET /get_return_updating_map_new_tick_start HTTP/1.1\r\n"
                    "Host: losbalderdash.com\r\n"
                    "Connection: close\r\n\r\n";

                socket.write_some(asio::buffer(sRequest.data(), sRequest.size()), ec);

            }

            // myAsioInstance = new myAsio();
            // std::this_thread::sleep_for(std::chrono::seconds(1));

            std::this_thread::sleep_for(std::chrono::seconds(2));
            GrabSomeData(socket);

            context.stop();


            if (thrContext.joinable()) {

                thrContext.join();

                std::cout << "if we are finished - close  " << " \n";


                socket.close();

            }
       
    }





    ~myAsio() {
        if (thrContext.joinable()) {
            thrContext.join();
            std::cout << "if we are finished - close  " << " \n";
            //socket.close();
        }
        context.stop();
        std::cout << "context stopped \n";
	}



private:


    asio::io_context context;
   // asio::ip::tcp::socket socket;
    //asio::ip::tcp::resolver resolver_;
    //asio::ip::tcp::resolver::results_type endpoints_;
	// Other members as needed
    asio::error_code ec;
    std::thread thrContext;
	//const int BUFFER_SIZE_l = 1 * 1024; // 1 MB buffer size
    const std::string aBound = gen_random(7);
  
};




myAsio *myAsioInstance = nullptr; 




// Initialize a Fibonacci relation sequence
// such that F(0) = a, F(1) = b.
// This function must be called before any other function.
void load_asio_and_init(
    const unsigned long long a,
    const unsigned long long b)
{
    index_ = 0;
    current_ = a;
    previous_ = b; // see special case when initialized

   // myAsioInstance = myAsio();


    CreateNewConsole(1024);



  //   asio::error_code ec;
  //   asio::io_context context;


  //   asio::io_context::work idleWork(context); // fake taskt to asi so the context does'n finish 
  //   std::thread thrContext = std::thread([&]() { context.run();  });

  //   //   C++   losBalderdash.com     ip 84.201.148.195          nginx 1.16.1

  //   asio::ip::tcp::endpoint endpoint(asio::ip::make_address("34.51.147.110:8000", ec), 80);
  //   asio::ip::tcp::socket socket(context);

 
  //   socket.connect(endpoint, ec);




  //   if (!ec) {
  //       std::cout << "Connected ! " << "\n";
  //   }
  //   else {
  //       std::cout << " Failed to connect to address : " << ec.message() << "\n";
  //   }


  //   if (socket.is_open()) {
		// GrabSomeData(socket);


  //             std::string sRequest =
  //         "GET /ehi?baton=los_oksd&dev_castle=102 HTTP/1.1\r\n"
  //         "Host: losbalderdash.com\r\n"
  //         "Connection: close\r\n\r\n";

  //    socket.write_some(asio::buffer(sRequest.data(), sRequest.size()), ec);

  //   }

  //  



   myAsioInstance = new myAsio();
  //// std::this_thread::sleep_for(std::chrono::seconds(1));
  // 



  //  std::this_thread::sleep_for(std::chrono::seconds(2));
  //  GrabSomeData(socket);

  //  context.stop();
  //  

  //  if (thrContext.joinable()) {

  //      thrContext.join();

  //      std::cout << "if we are finished - close  " << " \n";


  //      socket.close();

  //  }

    myAsioInstance->sendInitialData();

}

// Produce the next value in the sequence.
// Returns true on success, false on overflow.
bool isConnectingExists()
{
    // check to see if we'd overflow result or position
 
    return true;
}

// Get the current value in the sequence.
unsigned long long send_data()
{

    myAsioInstance->sendUpdateMap();

   // /send_update_map


    return current_;
}

void GetReturnUpdatingMapTickL()
{
    myAsioInstance->GetReturnUpdatingMapTick();
    //std::this_thread::sleep_for(std::chrono::seconds(2));
    //std::cout << "GetReturnUpdatingMapTickL \n";
    //std::cout << "GetReturnUpdatingMapTickL \n";
	//std::cout << "GetReturnUpdatingMapTickL \n";
}


void load_connectionIs(static bool& isInternetConnectionExists) {
    isInternetConnectionExists = true;
}




void print_los_data(const char* name, int value) {
	std::cout << name << " : " << value << "\n";
    //std::this_thread::sleep_for(std::chrono::seconds(2));

}

void print_los_data_char(const char* name, const char* myMessage) {
    std::cout << name << " - " << myMessage << "\n";

    size_t Size1 = strlen(myMessage); // 79 
    std::cout << name << " size  " << Size1 << "\n";

   // std::this_thread::sleep_for(std::chrono::seconds(2));

    //for (int i = 0; i < Size1; i++) {
      //  std::cout << "pure " << i << " " << myMessage[i] << " \n";
     //   std::cout << "- " << i << " " << (char)myMessage[i] << " \n";
    //    std::cout << "I " << i << " " << (int)myMessage[i] << " \n";
    //    std::cout << ". " << std::to_string(myMessage[i]) << " \n";
   // }

}

// Get the current index position in the sequence.
unsigned send_updates()
{
    myAsioInstance->GetReturnUpdatingMapTick();

    return index_;
}







bool RedirectConsoleIO()
{
    bool result = true;
    FILE* fp;

    // Redirect STDIN if the console has an input handle
    if (GetStdHandle(STD_INPUT_HANDLE) != INVALID_HANDLE_VALUE) {
        if (freopen_s(&fp, "CONIN$", "r", stdin) != 0) {
            result = false;
        }
        else {
            setvbuf(stdin, NULL, _IONBF, 0);
        }

    }

    // Redirect STDOUT if the console has an output handle
    if (GetStdHandle(STD_OUTPUT_HANDLE) != INVALID_HANDLE_VALUE) {
        if (freopen_s(&fp, "CONOUT$", "w", stdout) != 0) {
            result = false;
        }
        else {
            setvbuf(stdout, NULL, _IONBF, 0);
        }

    }

    // Redirect STDERR if the console has an error handle
    if (GetStdHandle(STD_ERROR_HANDLE) != INVALID_HANDLE_VALUE) {
        if (freopen_s(&fp, "CONOUT$", "w", stderr) != 0) {
            result = false;
        }
        else {
            setvbuf(stderr, NULL, _IONBF, 0);
        }

        // Make C++ standard streams point to console as well.
        std::ios::sync_with_stdio(true);
    }
    // Clear the error state for each of the C++ standard streams.
    std::wcout.clear();
    std::cout.clear();
    std::wcerr.clear();
    std::cerr.clear();
    std::wcin.clear();
    std::cin.clear();

    return result;
}



bool ReleaseConsole()
{
    bool result = true;
    FILE* fp;

    // Just to be safe, redirect standard IO to NUL before releasing.

    // Redirect STDIN to NUL
    if (freopen_s(&fp, "NUL:", "r", stdin) != 0) {
        result = false;
    }
    else {
        setvbuf(stdin, NULL, _IONBF, 0);
    }

    // Redirect STDOUT to NUL
    if (freopen_s(&fp, "NUL:", "w", stdout) != 0) {
        result = false;
    }
    else {
        setvbuf(stdout, NULL, _IONBF, 0);
    }

    // Redirect STDERR to NUL
    if (freopen_s(&fp, "NUL:", "w", stderr) != 0) {
        result = false;
    }
    else {
        setvbuf(stderr, NULL, _IONBF, 0);
    }

    // Detach from console
    if (!FreeConsole())
        result = false;

    return result;
}

void AdjustConsoleBuffer(int16_t minLength)
{
    // Set the screen buffer to be big enough to scroll some text
    CONSOLE_SCREEN_BUFFER_INFO conInfo;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &conInfo);
    if (conInfo.dwSize.Y < minLength)
        conInfo.dwSize.Y = minLength;
    SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), conInfo.dwSize);
}

void  CreateNewConsole(int16_t minLength)
{
    bool result = false;

    // Release any current console and redirect IO to NUL
    ReleaseConsole();

    // Attempt to create new console
    if (AllocConsole())
    {
        AdjustConsoleBuffer(minLength);
        result = RedirectConsoleIO();
    }

    //  return result;
}

