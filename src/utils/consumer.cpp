#include "consumer.h"
#include <iostream>
#include <cstring>
#include <signal.h>

Consumer::Consumer(const std::string &brokers, const std::string &topic) {
    std::string brokers_value = brokers;
    std::string topic_value = topic;
    char errstr[512];

    /* Create configuration objects */
    conf = rd_kafka_conf_new();

    /* Set configuration properties */
    rd_kafka_conf_set(conf, "bootstrap.servers", brokers_value.c_str(), errstr, sizeof(errstr));
    rd_kafka_conf_set(conf, "group.id", "my-group", errstr, sizeof(errstr));

    /* Create consumer instance */
    rk = rd_kafka_new(RD_KAFKA_CONSUMER, conf, errstr, sizeof(errstr));
    if (!rk) {
        std::cerr << "Failed to create consumer: " << errstr << "\n";
        rd_kafka_conf_destroy(conf);
        exit(1);
    }

    /* Create topic partition list and add topic */
    topic_list = rd_kafka_topic_partition_list_new(1);
    rd_kafka_topic_partition_list_add(topic_list, topic_value.c_str(), RD_KAFKA_PARTITION_UA);

    /* Subscribe to topic */
    if (rd_kafka_subscribe(rk, topic_list) != RD_KAFKA_RESP_ERR_NO_ERROR) {
        std::cerr << "Failed to subscribe to topic: " << rd_kafka_err2str(rd_kafka_last_error()) << "\n";
        rd_kafka_topic_partition_list_destroy(topic_list);
        rd_kafka_destroy(rk);
        rd_kafka_conf_destroy(conf);
        exit(1);
    }
}

Consumer::~Consumer() {
    /* Clean up resources */
    rd_kafka_topic_partition_list_destroy(topic_list);
    rd_kafka_unsubscribe(rk);
    rd_kafka_destroy(rk);
    rd_kafka_conf_destroy(conf);
}

void Consumer::consumeMessages() {
    while (run.load()) {
        rd_kafka_message_t *msg;

        msg = rd_kafka_consumer_poll(rk, 1000);  // Poll with a timeout of 1000ms
        if (msg) {
            if (msg->err == RD_KAFKA_RESP_ERR_NO_ERROR) {
                std::cout << "Received message (" << msg->len << " bytes): " << std::string((char *)msg->payload, msg->len) << "\n";
            } else {
                std::cerr << "Failed to consume message: " << rd_kafka_err2str(msg->err) << "\n";
            }
            rd_kafka_message_destroy(msg);
        }
    }
}

void Consumer::stop() {
    run.store(false); // Signal consumer to stop
}