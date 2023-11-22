#ifndef APICLIENT_H
#define APICLIENT_H

#include <HTTPClient.h>
#include <WiFiClientSecure.h>
#include "logger.h"

class APIClient {
	private:
		String _endpoint;
		String _host;
		String _apiKey;
		WiFiClientSecure *_wifiClient;
		HTTPClient *httpClient;
	public:
		Logger *logger;
		APIClient(String,String,String);
		int send(char*);
		void setLogger(Logger*);

};

#endif /* APICLIENT_H */