#include <iostream>

int main(int argc, char **argv) {
    std::string brokers = "127.0.0.1:19092";
    std::string topic = "orders";
    std::string message = "Sample message";

    std::cout << "Brokers: " << brokers << std::endl;
    std::cout << "Topic: " << topic << std::endl;
    std::cout << "Message: " << message << std::endl;

    return 0;
}
