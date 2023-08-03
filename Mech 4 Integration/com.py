from smbus import SMBus

addr=0x8
bus = SMBus(1)
def send(data):
    bus.write_byte(addr,data)
def request():
    return bus.read_byte(0x8)
    
