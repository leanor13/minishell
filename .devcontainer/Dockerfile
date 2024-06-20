
# Use an official Debian image as a parent image
FROM debian:latest

# Update and install gcc, g++, make, and valgrind
RUN apt-get update && apt-get install -y gcc g++ make valgrind libreadline-dev git x11-apps xterm zsh

# Install Python, pipx, and norminette
RUN apt update
RUN apt install -y python3-setuptools
RUN apt install -y pipx
RUN pipx install norminette
RUN pipx ensurepath

# Set the default shell to zsh
SHELL ["/bin/zsh", "-c"]

# Set the working directory in the container to /app
WORKDIR /app

# Start a shell when the Docker container runs
CMD ["/bin/zsh"]