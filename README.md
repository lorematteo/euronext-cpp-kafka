# Euronext C++ Kafka Router

## Prerequisites

Ensure the following tools and libraries are installed on your system:

- **Docker Desktop**: For containerized services.
- **C++ Compiler**: Compatible with C++17 or higher (e.g., GCC, Clang).
- **CMake**: For building the project.
- **librdkafka**: Kafka client library for C/C++.

---

## Launching the Redpanda Server

**Redpanda** is a Kafka-compatible streaming platform designed for high performance and simplicity.

1. Open a terminal and navigate to the Redpanda directory:
   ```bash
   cd /redpanda
   ```
2. Start the Redpanda server using Docker Compose:
   ```bash
   docker compose up
   ```
3. Once launched, access the Redpanda UI at [http://localhost:8080/](http://localhost:8080/).
4. In the **"Topics"** section, create a new topic named `orders` for later use.

---

## Configuring `CMakeLists.txt`

Before building the project, ensure the `CMakeLists.txt` file is configured with the correct paths:

```cmake
# Specify the include directory for headers
include_directories(src/include)

# Specify the include directory for librdkafka
include_directories(/opt/homebrew/include)

# Specify the library directory for librdkafka
link_directories(/opt/homebrew/lib)
```

---

## Building and Running the C++ Application

1. Create and navigate to the build directory:
   ```bash
   mkdir build
   cd build
   ```
2. Generate the build files with CMake:
   ```bash
   cmake ..
   ```
3. Compile the project:
   ```bash
   cmake --build .
   ```
4. Run the compiled executable:
   ```bash
   ./euronext-router
   ```

---

## Troubleshooting

- Ensure Docker is running before launching Redpanda.
- Verify `librdkafka` is correctly installed and linked during the build process.
- Use `docker ps` to confirm that the Redpanda containers are running.

For additional support, refer to libraries documentation or community forums.

