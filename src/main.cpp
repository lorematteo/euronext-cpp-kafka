#include <iostream>
#include "producer.h"

int main(int argc, char **argv) {
    std::string brokers = "127.0.0.1:19092";
    std::string topic = "orders";
    std::string message = "Sample message";

    Producer producer(brokers, topic);
    producer.produceMessage(message);

    return 0;
}
