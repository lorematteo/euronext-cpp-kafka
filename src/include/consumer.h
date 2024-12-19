#ifndef CONSUMER_H
#define CONSUMER_H

#include <librdkafka/rdkafka.h>
#include <string>

class Consumer {
public:
    Consumer(const std::string &brokers, const std::string &topic);
    ~Consumer();
    void consumeMessages();
    void stop();

private:
    rd_kafka_t *rk;                /* Kafka consumer handle */
    rd_kafka_conf_t *conf;         /* Kafka configuration */
    rd_kafka_topic_t *rkt;         /* Topic handle */
    rd_kafka_topic_partition_list_t *topic_list; /* Topic partition list */
    std::atomic<bool> run; // Thread-safe flag
};

#endif
