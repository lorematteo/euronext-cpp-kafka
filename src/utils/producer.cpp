#include "producer.h"
#include <string>
#include <iostream>

Producer::Producer(const std::string &brokers, const std::string &topic) {
    std::string brokers_value = brokers;
    std::string topic_value = topic;

    /* Create Kafka configuration */
    conf = rd_kafka_conf_new();

    /* Set the broker list */
    if (rd_kafka_conf_set(conf, "bootstrap.servers", brokers_value.c_str(), nullptr, 0) != RD_KAFKA_CONF_OK) {
        std::cerr << "Failed to set broker list\n";
        exit(1);
    }

    /* Create Kafka producer */
    rk = rd_kafka_new(RD_KAFKA_PRODUCER, conf, nullptr, 0);
    if (rk == nullptr) {
        std::cerr << "Failed to create Kafka producer\n";
        exit(1);
    }

    /* Create Kafka topic */
    rkt = rd_kafka_topic_new(rk, topic_value.c_str(), nullptr);
    if (rkt == nullptr) {
        std::cerr << "Failed to create Kafka topic\n";
        rd_kafka_destroy(rk);
        exit(1);
    }
}

Producer::~Producer() {
    /* Destroy Kafka topic and producer */
    rd_kafka_topic_destroy(rkt);
    rd_kafka_destroy(rk);
}

void Producer::produceMessage(const std::string &message) {
    std::string message_value = message;

    void *data = static_cast<void *>(const_cast<char *>(message_value.c_str()));

    rd_kafka_resp_err_t err = static_cast<rd_kafka_resp_err_t>(rd_kafka_produce(rkt, RD_KAFKA_PARTITION_UA, RD_KAFKA_MSG_F_COPY, data, message.length(), NULL, 0, NULL));
    if (err != RD_KAFKA_RESP_ERR_NO_ERROR) {
        std::cerr << "Failed to produce message: " << rd_kafka_err2str(err) << "\n";
        exit(1);
    }

    /* Wait for messages to be delivered */
    rd_kafka_flush(rk, 10000);
}
