#include <stdio.h>
#include <unistd.h> 
#include <fcgi_config.h>
#include <fcgiapp.h>

#define SOCKET_PATH "127.0.0.1:8080"

int main(void)
{
	int rc, socketId;
	FCGX_Request request;
	char *server_name;

	FCGX_Init();
	printf("Lib is inited\n");
	socketId = FCGX_OpenSocket(SOCKET_PATH, 20);
	if(socketId < 0)
	{
		//ошибка при открытии сокета
		return 1;
	}
	printf("Socket is opened\n");

	if(FCGX_InitRequest(&request, socketId, 0) != 0)
	{
		//ошибка при инициализации структуры запроса
		printf("Can not init request\n");
		return 2;
	}
	printf("Request is inited\n");

	for(;;)
	{
		//попробовать получить новый запрос
		printf("Try to accept new request\n");
		rc = FCGX_Accept_r(&request);

		if(rc < 0)
		{
			//ошибка при получении запроса
			printf("Can not accept new request\n");
			break;
		}
		printf("request is accepted\n");

		//получить значение переменной
		server_name = FCGX_GetParam("SERVER_NAME", request.envp);

		//вывести все HTTP-заголовки (каждый заголовок с новой строки)
		//между заголовками и телом ответа нужно вывести пустую строку
		FCGX_PutS("Status: 200 OK\r\n", request.out);
		FCGX_PutS("Content-type: text/html\r\n\r\n", request.out);
		//вывести тело ответа (например - html-код веб-страницы)
		FCGX_PutS("<html>\r\n", request.out);
		FCGX_PutS("<head>\r\n", request.out);
		FCGX_PutS("<title>FastCGI Hello World!</title>\r\n", request.out);
		FCGX_PutS("</head>\r\n", request.out);
		FCGX_PutS("<body>\r\n", request.out);
		FCGX_PutS("<h1>FastCGI Hello World!</h1>\r\n", request.out);
		FCGX_PutS("<p>Request accepted from host: <i>", request.out);
		FCGX_PutS(server_name ? server_name : "&ltunknown&gt", request.out);
		FCGX_PutS("</i></p>\r\n", request.out);
		FCGX_PutS("</body>\r\n", request.out);
		FCGX_PutS("</html>\r\n", request.out);

		// //"заснуть" - имитация многопоточной среды
		// sleep(2);

		//закрыть текущее соединение
		FCGX_Finish_r(&request);

		//завершающие действия - запись статистики, логгирование ошибок и т.п.
	}
	return (0);
}