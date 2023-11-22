#ifndef API_CLIENT_H
#define API_CLIENT_H

#include <HTTPClient.h>
#include <WiFiClientSecure.h>
#include "logger.h"

class APIClient {
	private:
		const char* endpoint;
		const char* host;
		const char* apiKey;
		WiFiClientSecure *wifiClient;
		HTTPClient *httpClient;
	public:
		Logger *logger{};
		APIClient(const char*,const char*,const char*);
		int send(const char*);
		void setLogger(Logger*);

};

#endif /* API_CLIENT_H */