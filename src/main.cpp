#include <iostream>
#include <thread>
#include "producer.h"
#include "consumer.h"

int main(int argc, char **argv) {
    std::string brokers = "127.0.0.1:19092";
    std::string topic = "orders";
    std::string message = "Sample message";

    Producer producer(brokers, topic);
    producer.produceMessage(message);

    Consumer consumer(brokers, topic);

    // Launch consumer in a separate thread
    std::thread consumerThread(&Consumer::consumeMessages, &consumer);

    // Perform other tasks in the main thread
    for (int i = 0; i < 5; ++i) {
        producer.produceMessage(message + " " + std::to_string(i));
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    // Clean shutdown
    std::cout << "Waiting for consumer to finish...\n";
    consumer.stop();
    consumerThread.join();

    std::cout << "Exiting program.\n";
    return 0;
}
