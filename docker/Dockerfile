FROM rockylinux:{{rocky-number}}
MAINTAINER Fabien MARTY <fabien.marty@gmail.com>

RUN yum -y install gcc make valgrind glib2-devel

ADD entrypoint.sh /entrypoint.sh
CMD /entrypoint.sh
