FROM debian:buster-slim as source
ARG branch=master

RUN apt-get update && DEBIAN_FRONTEND=noninteractive && apt-get install -y git
RUN git clone -b $branch https://github.com/everitoken/vast.git

FROM everitoken/pyvast:latest as pyvast
RUN python3 /pyvast/setup.py bdist_wheel


FROM everitoken/pyenv

WORKDIR /pysdk

COPY --from=pyvast /pyvast/dist/*.whl ./
RUN pip3 --no-cache-dir install *.whl
RUN rm *.whl

COPY --from=pyvast /usr/local/lib/*.so* /usr/local/lib/
COPY --from=source /vast/sdks/pysdk ./

ENV LD_LIBRARY_PATH /usr/local/lib
ENV PATH /usr/sbin:/usr/bin:/sbin:/bin

ENTRYPOINT ["python3", "-m", "pyvastsdk.unit_test", "http://118.31.58.10:8888"]
