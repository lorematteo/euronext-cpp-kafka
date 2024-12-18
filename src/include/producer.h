#ifndef PRODUCER_H
#define PRODUCER_H

#include <librdkafka/rdkafka.h>
#include <string>

class Producer {
public:
    Producer(const std::string &brokers, const std::string &topic);
    ~Producer();
    void produceMessage(const std::string &message);

private:
    rd_kafka_t *rk;         /* Kafka producer handle */
    rd_kafka_conf_t *conf;  /* Kafka configuration */
    rd_kafka_topic_t *rkt;  /* Topic handle */
};

#endif
