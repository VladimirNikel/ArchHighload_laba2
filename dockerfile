FROM ubuntu

RUN apt update
RUN apt install git -y
RUN apt install python3 -y

WORKDIR /home/app/

RUN apt install python3-pip -y
RUN pip3 install fastapi
RUN pip3 install uvicorn
RUN pip3 install pyowm

RUN git clone https://github.com/VladimirNikel/ArchHighload_laba2

CMD export OWM_APP_KEY=6e91084d708cf0dcdabc8e852960d090 && python3 ./ArchHighload_laba2/main.py