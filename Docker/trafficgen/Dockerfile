FROM debian:buster-slim as source
ARG branch=master

RUN apt-get update && DEBIAN_FRONTEND=noninteractive && apt-get install -y git
RUN git clone -b $branch https://github.com/everitoken/vast.git

FROM everitoken/pyvast:latest as pyvast
RUN python3 /pyvast/setup.py bdist_wheel

FROM everitoken/pysdk:latest as pysdk
RUN python3 /pysdk/setup.py bdist_wheel

FROM everitoken/pyenv

WORKDIR /trafficgen

COPY --from=pyvast /pyvast/dist/*.whl ./
COPY --from=pysdk /pysdk/dist/*.whl ./
RUN pip3 --no-cache-dir install *.whl
RUN rm *.whl

COPY --from=pyvast /usr/local/lib/*.so* /usr/local/lib/
COPY --from=source /vast/loadtest/trafficgen ./

ENV LD_LIBRARY_PATH /usr/local/lib
ENV PATH /usr/sbin:/usr/bin:/sbin:/bin
ENV LC_ALL=C.UTF-8
ENV LANG=C.UTF-8

VOLUME /opt/traffic

ENTRYPOINT ["python3", "-m", "trafficgen.generator", "-o", "/opt/traffic"]
