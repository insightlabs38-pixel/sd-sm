FROM gcc:15@sha256:eb5e64286ad47187b32bda75c6b6916166ecb41da56559b8b09e0001748d2cce AS build
COPY d_traverse.cpp pgo_train_graph.cpp /src/
RUN mkdir -p /mnt/champion-train /tmp/pgo /tmp/train-out && \
    g++ -O2 -std=c++17 -o /tmp/train-gen /src/pgo_train_graph.cpp && \
    /tmp/train-gen && \
    g++ -O3 -std=c++17 -pthread -flto -static -s -fprofile-generate=/tmp/pgo -fprofile-update=atomic -o /traverse /src/d_traverse.cpp && \
    SD_DATA=/mnt/champion-train SD_OUT=/tmp/train-out SD_THREADS=12 /traverse && \
    test -n "$(find /tmp/pgo -name '*.gcda' -print -quit)" && \
    g++ -O3 -std=c++17 -pthread -flto -static -s -fprofile-use=/tmp/pgo -fprofile-correction -fprofile-partial-training -o /traverse /src/d_traverse.cpp
FROM debian:13-slim@sha256:62bd423aeee912639ca8ee681c2b762cb3e25137e0a92b20be455898a9f034ad
COPY --from=build /traverse /traverse
ENTRYPOINT ["/traverse"]
