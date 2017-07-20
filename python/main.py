import cwiid
import time

wiimote = cwiid.Wiimote()

wiimote.rpt_mode = cwiid.RPT_BTN | cwiid.RPT_ACC

while True:
   bomb = 0
   beam = 0
   rotate = 0
   acc = 0

   f = open('wii_input.txt', 'w')
   po = wiimote.state['buttons']
   if po >= 2048:
       po = po - 2048
       rotate = 1
   if po >= 1024:
       po = po - 1024
       acc = 1
   if po >= 512:
       po = po - 512
   if po >= 256:
       po = po - 256
   if po >= 128:
       po = po - 128
   if po >= 64:
       po = po - 64
   if po >= 32:
       po = po - 32
   if po >= 16:
       po = po - 16
   if po >= 8:
       po = po - 8
   if po >= 4:
       po = po - 4
   if  po >= 2:
       po = po - 2
       bomb = 1
   if  po >= 1:
       beam = 1
   f.write(str(wiimote.state['acc'][0] - 120) + ' ' 
           + str(wiimote.state['acc'][1] - 120) + ' '
           + str(beam) + ' '
           + str(bomb) + ' '
           + str(rotate) + ' '
           + str(acc))
   print(str(wiimote.state['acc'][0] - 120) + ' ' 
           + str(wiimote.state['acc'][1] - 120) + ' '
           + str(beam) + ' '
           + str(bomb) + ' '
           + str(rotate) + ' '
           + str(acc))
   f.close()
   time.sleep(0.1)
