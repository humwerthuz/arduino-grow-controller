#include "ApiClient.h"
#include <string>
#include "constants.h"

APIClient::APIClient(const char* _host, const char*  _endpoint, const char* _ak){
    host = _host;
    endpoint = _endpoint;
    apiKey = _ak;
    wifiClient = new WiFiClientSecure();
	wifiClient->setCACert(google_apis_root_ca);
	httpClient = new HTTPClient();
	this->httpClient->setReuse(true);
}

void APIClient::setLogger(Logger *l){
	this->logger = l;
}

int APIClient::send(const char *payload){
	if (httpClient->begin(*this->wifiClient, this->endpoint)) {
		httpClient->addHeader("Content-Type", "application/json");
		httpClient->addHeader("x-api-key", this->apiKey);
		httpClient->addHeader("Host", this->host);
		int httpCode = httpClient->POST((uint8_t *) payload, sizeof(payload));
		if (httpCode > 0) {
			// Just read from buffer to avoid weird things
			httpClient->getString();
		} else {
            String errorString = HTTPClient::errorToString(httpCode);
            std::string buff = "[HTTPS] POST... failed, error: " + std::string(errorString.c_str()) + "\n";
			if ( this->logger != nullptr ) {
				this->logger->logError(buff.c_str());
			} else {
                log_e("Error on HTTP Client: %s", buff.c_str());
			}
		}
		httpClient->end();
  }
	return 0;
}