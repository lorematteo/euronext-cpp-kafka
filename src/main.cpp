#include <iostream>
#include "producer.h"
#include "consumer.h"

int main(int argc, char **argv) {
    std::string brokers = "127.0.0.1:19092";
    std::string topic = "orders";
    std::string message = "Sample message";

    Producer producer(brokers, topic);
    producer.produceMessage(message);

    Consumer consumer(brokers, topic);
    consumer.consumeMessages();

    return 0;
}
