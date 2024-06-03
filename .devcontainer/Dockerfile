
# Use an official Ubuntu image as a parent image
FROM ubuntu:latest

# Update and install gcc, g++, make, and valgrind
RUN apt-get update && apt-get install -y gcc g++ make valgrind libreadline-dev git x11-apps xterm

# Set the working directory in the container to /app
WORKDIR /app

# Start a shell when the Docker container runs
CMD ["/bin/bash"]