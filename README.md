# AlterWear
## new [eink](https://learn.adafruit.com/adafruit-eink-display-breakouts/arduino-code)
- image needs to be correctly formatted
- using NFC 13 SP app from EINK. 
- have to hold it there a few seconds while it does redraw
- EINK 101 may be getting setup.
- Separate NDA from fancy new tech that's not even released. Start simple, get flexible material.

## Basic E-Ink Setup

- NT3H1101 NFC chip
- [Arduino Pro Mini (Atmega328)](https://learn.sparkfun.com/tutorials/using-the-arduino-pro-mini-33v)
- eink_i2c code

### Hardware
**Correct datasheet, we think**
- The working one is [here, which has been discontinued.](http://www.pervasivedisplays.com/kits/ext_kit). The datasheet is "EPD Extension board_Schematic_Gerber_v05". The files are available at that link, but also uploaded to this repo.
- Pervasive Displays (e-ink manufacturer) [support](http://www.pervasivedisplays.com/contact). Definitely contact them if you have issues! They should help you with specific questions.

**Another datasheet, not sure what it is for**
- This is a screenshot of ANOTHER circuit diagram [Fig. 5-1](https://www.dropbox.com/s/spbxfzleej3tsp5/Screenshot%202018-02-21%2015.26.41.png?dl=0) from the datasheet.
- PDF [datasheet for the e-ink display.](http://www.pervasivedisplays.com/LiteratureRetrieve.aspx?ID=232432) 
Screenshot.

**Circuit Diagram for Paul Schow's E-Papercard:**
https://github.com/paulschow/epapercard/blob/master/Sch_Aug_14.pdf

**label info**

|Name|Digit# (Code)|2|3|4-6 (Display size)|7 (FPL Material)|8 (S?)|9-11 (Serial Number)|extras|code|
|---|---|---|---|---|---|---|---|---|---|
|rhonda (cracked)|C|E|G|020 (G2?)|A|S|012 (G1, eTC)|28X0497|?|
|phuong|V|E|2|200|C|S|021 (G2, eTC)|02573P000462|V231-G2|
|felicity (cracked)|L|E|1|144|C|S|021 (G2, eTC)|01465T2PK2|V231-G2|
|ijeoma|V|E|2|200|C|S|021, (G2, eTC)|02573P000454|V231-G2|
|purse|L|E|1|144|C|S|021 (G2, eTC)|01465T2PK2|V231-G2|
|spongebob|L|E|1|190|C|S|021 (G2, eTC) |01466D0T32|V231-G2|
|fei hung (cracked)|L|E|1|144|C|S|021 (G2, eTC) |01465S1N62|V231-G2|

FPL Material "C" = Aurora Mb (V231), and:

- if digit#10=1, G1 (eTC)
- if digit#10=2, G2 (eTC)
- if digit#10=5, 6, 8 or 9 is iTC


### Arduino Software
#### Default (Arduino UNO and GRATIS library)
1. Download the Arduino library from Adafruit's [tutorial on how to use the e-ink display board](https://learn.adafruit.com/repaper-eink-development-board/overview) we have.
2. Once you've installed the library, the library code we want is EPD_V230_G2 --> demo_200 (should work out of the box).


#### Arduino Pro Mini
1. The Arduino Pro Mini is programmed over FTDI (3.3V I think).

#### Experimental
1. Paul Schow's github: https://github.com/paulschow/epapercard
(specifically firmware -> paul_demo_200, which is an updated, simplified version of the same library w/ "excess" parts removed.)
2. "Our" version of Paul's code: https://github.com/molecule/epapercard
3. Paul Schow's blog: https://www.paulschow.com//2016/08/epaper-business-card.html?m=1
 
## Basic NFC Setup on Uno

Notes: I2C communicates over 2 lines (SDA and SCLK). These both need pull-up resistors because they are "open drain".[2] According to [1], the tag click has pull-up resistors on SDA and SCLK already. Table 15[3] says the I2C address is 04h. [A good tutorial on I2C from Sparkfun](https://learn.sparkfun.com/tutorials/i2c). Uno: A4 (SDA), A5 (SCL).

0. Note that the NFC cannot be connected to Tx, Rx while uploading.
1. Connect GND, 3.3V to the Arduino power pins. Connect SDA to A4 and SCL to A5.
3. Use eink_i2c (which use Wire library) to read from NFC and update code.


2. Possibly relevant:
   - https://community.nxp.com/message/977712?commentID=977712#comment-977712
   - Confirmed we're using the NT3H1101 (in the paper). [Datasheet](https://www.nxp.com/docs/en/data-sheet/NT3H1101_1201.pdf). Ch. 9.6 has addressing info. I believe it's 85, 0b1010101, or 0x55. 
   - Trying to use this library: https://www.arduino.cc/en/Reference/Wire
   - I contacted Angela Lee via NXP: https://community.nxp.com/thread/469669
   - Info re: I2C: https://howtomechatronics.com/tutorials/arduino/how-i2c-communication-works-and-how-to-use-it-with-arduino/
   - Added a follow-up to this comment: https://community.nxp.com/message/1026052

## NFC on Arduino Pro Mini
Note: Somehow this pro mini 3.3v w/ FTDI cable really messes up my USB ports on my Mac (need to restart my computer to reset them).

0. Connect PWR and GND like normal, solder the two little extra pins (A4, A5) in the middle of the board next to A3. This is what connects to the SDL and SCLK of the NFC board).
1. Use eink_i2c.

[1][Potentially slightly useful NFC tag docs.](https://download.mikroe.com/documents/add-on-boards/click/nfc-tag/nfc-tag-click-manual-v100.pdf)

[2][How To Mechatronics - I2C](https://howtomechatronics.com/tutorials/arduino/how-i2c-communication-works-and-how-to-use-it-with-arduino/)

[3][NT3H2111_2211 Datasheet](https://download.mikroe.com/documents/datasheets/NT3H2111_2211.pdf)
(Relevant portion [here](https://www.dropbox.com/s/d4i99ricvakj35r/Screenshot%202018-06-27%2012.02.47.png?dl=0) )

## Making custom images
[These instructions from alexhadik.com](http://www.alexhadik.com/blog/2014/10/30/display-custom-e-ink-images-with-repaper-and-arduino-uno) were very helpful. 

Dimensions:

- 1.44": 96x128 pixels
- 2": 96x200 pixels
- 1.44": 176x264 pixels

Steps summarized here:

1. For a 2.0" board, open an Illustrator file.
2. Create an artboard that is 95x199 pixels in dimensions (note: one pixel smaller than you want the final one to be).
3. The image should be longer than it is wide.
4. Export that artboard as a jpg. Make sure it is now 96x200 pixels.
5. Using [this web app](https://www.online-utility.org/image/convert/to/XBM), convert to xbm.
6. Validate the file was built correctly:

You'll want to open your image files in a text editor like Sublime or Atom and check that the first lines have the following format:

```
#define myimage_2_0_width 200
#define myimage_2_0_height 96
static unsigned char myimage_2_0_bits[] = {
    ...
}
```

That is, the #define and char array declaration are named the same as your file and have the proper width, height, and screen size set. Open some of the images that exist in the Images directory for reference if you like.
7. Add your new xbm file to Arduino/libraries/Images
8. That should work.

## Breakout board notes

How to find the COG #:
- official page: http://www.pervasivedisplays.com/products/label_info
- semi-helpful Adafruit forum thread: https://forums.adafruit.com/viewtopic.php?f=19&t=56535&start=15

EPD breakout board (green):
- Compatible with: 40+pin e-ink display (connector is zig-zag).
- Goals: Recreate it on the breadboard, then simplify if possible, then create an SMD version.

Teensy e-paper adapter board (red): https://hackaday.io/project/13327-teensy-e-paper-adapter-board
- Original crowdsource campaign: https://www.crowdsupply.com/soniktech/e-paper-shield-kit
- Library code and example: https://github.com/jarek319/EPD215
- Compatible with: 20+-pin e-ink displays (connector is straight).
- Goals: Get it working (library code freezes and we don't know why), recreate and build our own.

## TI CCStudio 
- Download from here: http://processors.wiki.ti.com/index.php/Download_CCS
- Phenomenal set of tutorials: http://mspsci.blogspot.com/2010/07/tutorial-05-loading-program.html
- More tutorial links: https://43oh.com/2010/08/10-beginner-msp430-tutorials-and-counting/
- One more: http://processors.wiki.ti.com/images/f/f7/LaunchPadSimpleProject.pdf

## Compare w/ Paperino

|Spec | Paperino | EPD|
|---|---|---|
|# pins| [11](https://robpo.github.io/Paperino/) | [14](https://learn.adafruit.com/repaper-eink-development-board/wiring-the-uno-and-leonardo)
| Power | [4.5 mA (mean current for typical image update)](https://www.crowdsupply.com/robert-poser/paperino) | [6mA 2.7V 2.4 sec](http://www.hybrid-ecologies.org/uploads/project/paper/24/18_CHI_AlterWear.pdf)|

## Other notes
- Technical support email: 	techsupport@pervasivedisplays.com
- [Old badger link.](https://web.archive.org/web/20170802044828/http://wyolum.com/projects/badger/)
- [BADGEr code](https://github.com/wyolum/EPD)
- [BADGEr v4 from Seeed Studio ($50)](https://www.seeedstudio.com/BADGEr_v4-p-1587.html)
- [Instructions from MSR for making custom e-ink thing.](https://ieeexplore.ieee.org/stamp/stamp.jsp?tp=&arnumber=7508851)
- [Semi-helpful review from Paul Schow](https://www.paulschow.com/2017/02/pervasive-displays-epd-extension-kit.html).
- [Much more helpful review](https://embeddedcomputing.weebly.com/pervasive-displays-e-paper-epd-extension-kit-gen-2.html)

To debug from the .cpp library code, just add Serial.print() statements - they show up like normal in the serial monitor.

## ~~2019-04-03 Plan~~ 2019-04-17 notes
- IRB
    - Complete, ~~needs Eric to check the assurance box, then we can submit.~~ Submitted, got comments back.
    - change recruitment stuff (find 'fashionable' people). (Christie) **Did we do this? Or do we need to?**
- Study
    - Find groups on campus we'd like to recruit from and reach out to the club leaders.
        - EthiCal, sell tshirts on Sproul. [link](https://ethicalapparel.org/)
	- Innovative Design, big graphic design club [link](https://innovativedesign.club/)
	- Berkeley Innovation, UI/UX design club. [link](https://www.berkeleyinnovation.org/)
	- DeCal something related to Q New Media.
	- Jill's undergrad class? Critical Practices project?
	- Sports clubs? Intramural / recreational?
	- Origami (visual, crafting)
	- Outlet art club.
	- Comics Decal.
    - Finalize form factors (depends on HW), update IRB if needed.
- HW / SW
    - The HW Eink brought is not useful for us. They therefore didn't share any code / datasheets, and aren't sure on whether that would be available. **Any update on this?**
    - For now, Adafruit eink as dev HW.
    - update Android apps to be one single app. (Ariana)
        - Arianna has moved all the apps to one app, and is now working on passing data from one activity to another. So, for example, you could take a picture, then load it into the "drawing" app, draw on the picture, then load it into "find edges" and find the edgs of your combined drawing and picture.
	- We also thought through some UX details, and decided the end goal for the semester is an app where you pass bitmaps around between the different activities, editing as you go. We will leave the "pass to eink display" as code stubs for future decision once the HW has been finalized.
- Feather assessments: NONE CAN BE POWERED BY NFC!
    - [ATSAMD51](https://www.adafruit.com/product/3857) does have low powermode according to [datasheet](https://www.microchip.com/wwwproducts/en/ATSAMD51G19A), unclear if it's used in adafruit's board. 512KB Flash and 192KB RAM
    - [ATSAMD21](https://www.adafruit.com/product/2995). Has bluetooth nRF51 (BLE). Lacks extra storage.
    - Atmega328p
    - Basic Feather [Atmega 32u4](https://www.adafruit.com/product/2771) The one we have. 32K of flash and 2K of RAM
- Adafruit eink
    - takes several seconds to update.
    - shouldn't refresh or change the display more than every 3 mins.
- Paperino
    - [tried](https://robpo.github.io/Paperino/) on Particle Photon board, but Photon board literally died while I was trying to upload to it.
    - Next trying to compile example code for Pro Trinket, and getting compile errors: /Users/molecule/Documents/Arduino/libraries/PL_microEPD/src/PL_microEPD.h:83:43: error: overflow in constant expression
     byte buffer[EPD_WIDTH * EPD_HEIGHT / 4];
    - No related issues in the github so [I made a new github issue](https://github.com/RobPo/Paperino/issues/14), and hasn't been updated for 10 months.
    - Is the firmware for the pro mini not able to handle this buffer size? Or maybe the code is just making assumptions?

## 2019-03-06 Plan
- IRB
    - add group version. DONE. Ex from Noura is in the drive.
    - change recruitment stuff (find 'fashionable' people). (Christie)
    - consider working w/ a club/ sports team / group (advantages: maybe single form factor).
- Finalize form factors (depends on HW)
- HW / SW
    - get source code (of android app, firmware? interface?) (Christie email)
    - get datasheets (Christie emailing)
    - HW workshop 3/27 (scheduled)
    - update Android apps to be one single app. (Ariana)

## 2018-12-10 Plan for Spring Semester
- Hardware: 
  - debug
  - design
  - integration w/ textiles (Arianna)
- Software:
  - Firmware (running on Arduino) (Arianna)
  - App (running on phone) (Arianna)
- User study design + logistics (Arianna)
  - Update IRB if needed

## 2018-10-09 Eric meeting
- Going down to Eink to visit on Oct 26th. 
- 10:30am - tour, Eric will give a presentation. Interact w/ team, Q&A and brainstorming. Lunch.
- Eric must be back to pick up kids by 3pm. (so leave around 1pm?)
- They are excited to work with us.
- Trying to bring across the rest of the research team to being on our side/excited about our vision.

### Demos
- Want to show them something different from what we have shown them so far.
- We want them to give us access to more material, access to proprietary things (unlikely), funding/resources to support the research (pending IP agreement).
- eink story
- demo 1: take pic, it gets turned into bitmap, gets sent across NFC, updates to screen.
- display algs: standard, RLE, pattern + repeat.

#### Effects
- Videos of different eink image effects.
- Purse physical artifact
- Sending over 100 (or appropriate # of bits from phone?)
- Edge detection on phone
- drawing application

### Plans

- Android **Step 3**
  - Filter a photo
  	- CD: see if there are existing android libraries to convert a photo to black and white only (no grayscale), convert black and white to bitmap, etc. 
  - Send bitmap (RLE, or other compression schemes).
  - 
- NFC **Step 2**
  - Pass-thru mode?
  - Otherwise, store bitmap? 888 bytes of freely-available user-writable memory. **Step 2.1**
  - Rx bitmap?
- Arduino
  - Might not need to change this at all.
  - Do reconstruction on the Arduino?
- Eink
  - **Step 1** weird interlacing, bitmap tweaks, dithering algs, etc. Cool effects. Ability to draw. 8-bit aesthetic, etc.
  - Speed up updates, what's the fastest time we can update stuff.
    - Setup a github w/ [a version of the EPD library](https://github.com/molecule/AlterWear-libraries) we can alter/edit to our heart's desire.
  - Understanding library more (partial update????)

## Long-term wishlist TODO
1. Test epapercard stuff
  a. Get MSP430 running.
  a. Figure out how epapercard pinouts map from MSP430 to Arduino.
  c. Update arduino code for epapercard test.
  b. Edit Eagle file to work w/ Arduino.
3. NFC updates
  a. Look at new NFC chip options for something w/ more memory.
4. Build EEPROM break-out.
5. ~~Add rest of eink displays to info chart so I know what the heck I'm working with.~~
6. Compare w/ Paperino.
8. Try "partial update".
9. Image updates
  a. Fix line in trip_ images - make smooth.

## Current Status

#### 26 October 2018
- Hue told me their requirements at the first meeting: could have structured all of our presentation around that. (large size, commercial applications). 
- They wanted to know what we found hard, what types of tech we needed going forward, pain points for us. 
- Eric did a lot of work to build credibility (position us as "ahead of the curve": what seemed wacky in the past actually resulted in changes later: Apple implemented Eric's weird watch thing ~15 years later, Beam robots exist now and that was Eric's early work).
- Their work is so commercial application-ey, so it's a little hard to understand how to bridge our creative approach, which focuses on interaction styles, and map it to their interests/requirements.
- Question: What do they need / what are their phrases / arguments they need for their internal conversations?
- We emphasized documentation and software as pain points and support needs.
- Craig wanted to know what colors we wanted, and what other capabilities we thought were important - it seemed like they were going to decide on their engineering efforts based on our recommendations (don't feel like we are actually the experts here).

#### 23 October 2018
**TODO**
1. Slideshow of what we've done, challenges, videos of working stuff, discussion of vision.
2. Downsample to smaller number of bits (whatever that version is for eink displays).
3. Interlacing
4. A return to 8-bit aesthetics. 8-bit aesthetics temporally.
5. Capacitor charge on microcontroller 

**Notes**
1. Timing of writing to EEPROM 
- time to write 30 bytes: 98.00ms
- time to write 100 bytes: 333.00
- time to write 200 bytes: 669.00

#### 22 October 2018
1. Added a new image to the Images folder, penguin_cow.xbm. It can be flipped vertically, and looks either like a penguin or a cow depending on the orientation.
2. Tried to make a lenticular image, so that you see two different images depending on whether only the even lines are displayed or the odd lines. However, creating this in Adobe Illustrator was difficult. We could do this more easily by writing a script that would take 2 images that are both half the size as the e-ink screen, and then interweave them line by line. 
3. Additional idea: overlay 2 images slowly over time with moire pattern

#### 18 Oct 2018
**Notes**
1. Following up on ascii-binary converter, that works now. So now I need to try and pass that in to the library, have it repeat properly, and display it on the eink to make sure it's in the right format/order. I assume there should be no spaces since those will show up as zeroes from the converter, so just a long string of image bits should do it.
2. Created a simple image (pattern-simple) and noticed that the right-most line is 0x3c, and the next line over is 0xff (If I'm interpreting this layout correctly....). (ok I am).
3. Tried to read in more than 8 bytes of data from i2c on the arduino (sending a larger chunk over from Android). Didn't work: first 16 bytes are header + some data, then next seems to be noise. Maybe need to do another loop? ~~Don't really understand how to read "a 16-byte chunk" when it looks like it's just~~ Yep: at top of loop is request for another 16. 2nd loop should do it. state machine will be a teeny bit annoying.


#### 17 Oct 2018
**TODO**
1. Need an ASCII-binary converter in arduino to read ascii bits sent over from NFC
- https://forum.arduino.cc/index.php?topic=241663.0
- https://forum.arduino.cc/index.php?topic=117999.0
- https://www.arduino.cc/en/Tutorial/ASCIITable

**Notes**
1. Edited i2c-basic-test to be even more basic.
2. All it does is read first 16 bytes from Wire/i2c off NFC and prints them out.
3. Now, I'm sending "0xFF, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0xFF" from Android, hoping to be able to send bitmap-style bits over NFC.
4. Here's what's received on the Arduino (remember user-defined bits start at 10 because the first 9 bytes are ntag metadata) (using [this ASCII table](https://www.ibm.com/support/knowledgecenter/en/SSLTBW_2.3.0/com.ibm.zos.v2r3.ioaq100/ascii_table.gif)):

```
i: 10, byte: 48		0
i: 11, byte: 120	x
i: 12, byte: 70		F
i: 13, byte: 70		F
i: 14, byte: 44		,
i: 15, byte: 32		(space)
i: 16, byte: 48		0
```

So, clearly it's sent from Android and passed across NFC to Arduino as a string.

5. Created read-bytes-from-nfc.ino to try parsing the ints.
6. Now sending "FF FF 00 FF 00 FF FF"
7. Here's what i see on Arduino.):

```
i: 10, byte: 70		F
i: 11, byte: 70		F
i: 12, byte: 32		(space)
i: 13, byte: 70		F
i: 14, byte: 70		F
i: 15, byte: 32		(space)
i: 16, byte: 48		0
```


#### 11 Oct 2018
**Status**
1. We successfully uploaded to launchpad via TI CCSTUDIO.
2. We got paul's demo code + libraries compiling on both Windows and Mac.
3. We updated the github repo for our branch of paul's code to have a more sensicle layout.
4. ~~Still getting upload errors on both Windows and Mac.~~ FIXED! See 5.
    1. Windows: tilib: MSP430_Initailize: Could not find MSP-FET430UIF on specified COM port (that's a [debugging interface](http://www.ti.com/tool/MSP-FET430UIF) that it shouldn't actually need, according to this [forum post](https://e2e.ti.com/support/microcontrollers/msp430/f/166/t/264967?Error-Could-not-find-MSP-FET430UIF-on-specified-COM-port#pi320098=1)).
    2. Mac: Unable to find .hex file, but it's there and readable (same error as [this post](https://forum.43oh.com/topic/13296-mac-no-such-file-or-directory-when-uploading/)).
5. Switched over to using [PlatformIO for VSCode](https://docs.platformio.org/en/latest/ide/vscode.html#installation), [rearranged the libraries](https://www.dropbox.com/s/0twl3np2yw8q0iv/Screenshot%202018-10-11%2017.31.50.png?dl=0) according to the VSCode readme, and it uploaded w/ success! Need to confirm that it was *actually* successful (w/ blink?), then continue testing the fresh HW.
  

#### 15 Aug 2018
**Notes**
1. Getting RLE running in python.

#### 13 Aug 2018
**Questions for eink folks**
1. High contrast
2. Color options.
3. Lower power 
  a. bigger displays!
4. Faster update + partial
5. More sizes / resolution
6. No glass / flexible
7. Store image on eink directly.

**Notes from meeting with eink**
1. Overview of all of our research projects.
2. All-body compatible (communication, programming, privacy, security, aesthetic/fashionable, etc.)
3. "Appeal to everyone equally but no one deeply."
4. Exploring "cosmetics" as "a new vertical."
5. Small range NFC (1-3 meters).
6. 5 volt samples from the lab (not available w distribution).
7. Moving to 3.5 and on to 2 volt.
8. Question is: why lower voltage?
9. "Our interest is the creative mind you and your teams may be able to contribute."
10. [idea: design touchable eink display?]
11."exploratory is like a scout"
12. align expectations first
  a. access to products/materials (more flexible, lower voltage, colors, sizes, programming, etc.
  b. gift (financial support, materials).
  c. Advance notice of publication stuff.
  e. eink: non-proprietary limits us to applications. next 10-15 years future of the company, but it's all NDA. 
  f. Dress not a new concept. Tie, or belt would be not totally new, but a new way of using epaper.
  g. actually new: new use model, new digital lifestyle, 
  h. data channel that resulted in emojis, text messages, etc.
  i. wishtlist from cosmetic companies: perfect makeup. epaper eyeshadow/eyebrow?
  j. no one has been introduced to the idea that "things that you wear on your body change".
  k. small space resutls in worse performance: not enough "white" to provide contrast.
  l. nail printer.
  m. wear a smart nail, packaging also has epaper, could be linked. Ex: show your skin allergies on the packaging. Minority Report cereal box advertisements.
  n. [what do we want from the world where everything is dynamic?]
  o. weavable eink film only (very new, NDA etc.). Smart fiber!!!!
  p. details of relationship
    a. We contribute ideas, they do the prototyping. (Then we're consultants: a different relationship).
    b. JDA - paid financial sponsor.
    c. Consultancy (also involves NDA)
    d. Publication of application is ok: press release would fit w their goals. 
    e. Partnership w Citris - broader connection to University folks.
    f. Fake prototype w/o actual technology (but if we have a sponsored agreement, need to have some kind of agreement).
    g. If they pay, they need an "agreement" (collaboration, consulting, development) (and any agreement has NDA terms and IP terms).
  q. We're interested in prototypes in this landscape (wearables, body-based, IoT / wireless, smart packaging).

**TODO**
1. Figure out why the Arduino Pro Mini is so special/can be powered w/ such low power.
  - No idea....it is the same Atmega328 chip we've been using, and the [datasheet](https://store.arduino.cc/usa/arduino-pro-mini) says it runs at 3.3v. I don't understand how it's working at all.
2. ~~Edit app to measure timing of sending 800 bytes to NFC.~~ 
  - 800 bytes takes 1480 ms, 1 byte takes 62 msec.
  - 4 single byte messages takes 109ms.
  - 4 800-byte messages errors out w/ I/O exception.
  - So to send over all of a 15KB file in 800 byte chuncks (~19 chunks) would be 1480ms x 19 = 28120ms = 28 seconds.
  - Need NFC w/ bigger memory!
  - But this could work w/ delayed updating, and tricks w/ image techniques, plus if you just leave your phone in your purse.
  - Could you "send over the bits, and then only turn the display on once everything's there?
3. Figure out why app will only talk to the round NFC Tag2Clicks, not the rectangular ones. 
  - Weirder: old version of the app w example code from NXP works fine w/ all of them!
4. Measure timing of updating eink display.
5. Confirm 'faster' version of eink updating just removes certain update things.
  - Sort of. See notes below on partial update.
6. Fix hole in purse.
7. [etc vs itc](http://www.pervasivedisplays.com/products/eTC_vs_iTC).
  - etc: waveform comes from microcontroller, itc: waveform comes from driver IC (in both cases you send the image bits over).
8. Partial update:
  - V2 (V230+G2, also called Aurora Ma) IC **CANNOT run partial update?** ([src: github issue 19](https://github.com/repaper/gratis/issues/19))
  - V231 (also called Aurora Mb) and embedded G2 IC. **CAN run partial update?** ([src: github issue 19](https://github.com/repaper/gratis/issues/19))
  - If pixel is the same color, send the "nothing" byte, otherwise send the new pixel value.
  - Skips the inverse color steps (possibly degrades display). Also keeps the display on (so uses more power, but doesn't need to spend time powering on or off).
  - "stage time" (1.44" and 2" takes 480ms, 2.7" takes 630ms) (reducign this increases ghosting but speeds things up). (**what is stage time?**).
  - Even w max refresh rate of 2 Hz, the delay in the partial update is on the order of several 100 msec.
  - PDI releases the code upon request (I have it). [Youtube demo](https://www.youtube.com/watch?v=enzUbiSWenQ). [Another video shows update rate of 400ms and 100ms, w extensive ghosting.](https://www.youtube.com/watch?v=ArHd-TPkpxg)
9. Buffering:
  - Image bits are stored on PROGMEM of Arduino.
  - EPD library reads bits directly off PROGMEM, gets read via pgm_read_byte_near 

#### 12 Aug 2018
**TODO**
1. ~~Test~~ nevermind: powering from NFC doesn't work on Trinket boards...I don't really get why the Arduino Pro Mini is so special....need to figure that out). 2, ~~3~~ (doesn't power the Pro Trinket 5V which [requires at least 5v](https://learn.adafruit.com/introducing-pro-trinket/pinouts) to power on), 4 below w/ NFC.
2. Commit to constructing eink in purse based on what works.
5. HOW MUCH POWER does the NT3H1101 NFC generate? (Pin7 is VOUT so that's what to measure if it's not in the [datasheet](https://www.nxp.com/docs/en/data-sheet/NT3H1101_1201.pdf).
  - At room temperature, NTAG I2C could provide typically **5 mA at 2 V on the VOUT pin** with an NFC Phone.
  - A significant capacitor is needed to guarantee operation during RF communication. The total capacitor between VOUT and GND shall be in the range of 150nF to 200 nF. NOTE: According to the [NFC Tag2Click schematic](https://download.mikroe.com/documents/add-on-boards/click/nfc-tag-2/nfc-tag-2-click-schematic-v101-a.pdf) ([image here](https://www.dropbox.com/s/pm0wea8qz3n9nnq/Screenshot%202018-08-12%2018.39.11.png?dl=0)), this capacitor exists on the board we have.
  - If NTAG I2C also powers the I2C bus, then VCC must be connected to VOUT, and pull-up resistors on the SCL and SDA pins must be sized to control SCL and SDA sink current when those lines are pulled low by NTAG I2C or the I2C host. NOTE: I am not sure I see these in the [schematic image](https://www.dropbox.com/s/pm0wea8qz3n9nnq/Screenshot%202018-08-12%2018.39.11.png?dl=0).
  - If NTAG I2C also powers the Field Detect bus, then the pull-up resistor on the Field Detect line must be sized to control the sink current into the Field Detect pin when NTAG I2C pulls it low
  - The NFC reader device communicating with NTAG I2C shall apply polling cycles including an RF Field Off condition of at least 5.1 ms as defined in NFC Forum Activity specification (see Ref. 4, chapter 6).
  - Note that increasing the output current on the Vout decreases the RF communication range.
3. Add rest of eink displays to info chart so I know what the heck I'm working with.
4. Build break-out board for SparkFun external EEPROM memory.

**Notes**
1. Helpful Arduino pinouts for transferring circuits to other microcontrollers: https://github.com/damellis/attiny/blob/master/variants/tiny8/pins_arduino.h
2. Successfully powered eink display from ATTiny85 w/ battery connected. (left NFC phone at home so couldn't test it).
3. Built a circuit w/ teeny nail eink display attached to Pro Trinket. Works w/ usb power: haven't tested w/ NFC connection.
4. Built incomplete circuit w/ EPD breakout + Pro Trinket w/ edited lines in EPD_pinout.h (below). Need to test w/ eink display connected, and with NFC power: 

``` 
const int Pin_PANEL_ON = 2; // originally 2, moved to 10 to try to get things working on Pro Trinket
const int Pin_BUSY = 15; // originally 7, moved to 15 to try and get things working on Pro Trinket 
``` 
5. Why didn't it power the Pro Trinket? Was it the breadboard?
  - Attiny85: Operating Voltage: 2.7 - 5.5V for ATtiny25/45/85;  Power Consumption Active Mode: 1 MHz, 1.8V: 300 µA;
  - Atmega328p: Operating Voltage: 1.8 - 5.5V; Power Consumption at 1MHz, 1.8V, 25degC, Active Mode: 0.2mA
  - Note: Pro Trinket 5v needs 5V minimum to turn on. Should test w/ Pro Trinket 3.3v, and ideally an actual bare Atmega328p chip.

#### 10 Aug 2018
**TODOO**
1. ~~App is acting weird: won't dismiss the pop-up after tagging. Need to debug.~~ Done.
2. ~~Arduino Uno needs more power than NFC can provide - need to test changing pic on large eink display w/ an AtTiny85? Christie should have a circuit on her desk.~~
3. Then need to test whether you can send an entire image over....I'm not sure we ever looked at this! Everything is a lie.
4. Build break-out board for SparkFun external EEPROM memory.

#### 2 Aug 2018

**Notes**
1. From the rev3 user manual (in docs), [you have to use the CCStudio for some displays. You also need to change a setting (haven't figured that out yet)](https://imgur.com/a/5C6jD5s) Still haven't been able to verify what type of display we have.

#### 23 July 2018
**TODO**
- Consider adding more external memory: Could buy [this from Sparkfun](https://www.sparkfun.com/products/525) to increase size of EEPROM to 32kB (3200 Byte) of non volatile memory. Library to manage external memory: http://forum.arduino.cc/index.php?topic=502117.0
- Look at encoding / compression schemes:
    - http://shodhganga.inflibnet.ac.in/bitstream/10603/201087/8/08_chapter%201.pdf
    - http://flif.info/publications.html
    - https://maximumcompression.com/data/bmp.php
    - http://xooyoozoo.github.io/yolo-octo-bugfixes/#zoo-bird-head*1:3&bpg=t&jpg=t
    - https://bellard.org/bpg/
    - https://bellard.org/bpg/bpg_spec.txt
    - https://homepages.cae.wisc.edu/~ece533/project/f06/aguilera_rpt.pdf
    - https://arxiv.org/pdf/1211.4591.pdf
    - https://arxiv.org/pdf/1112.2261.pdf

**Notes**
- For EPD 2_0: ``` this->bytes_per_scan = 96 / 4; ```
- Overall flow is this:
Image_0 in EPD_V231_G2.h passes the byte pointer to the image (presumably):
```
// assuming a clear (white) screen output an image (PROGMEM data)
	void image_0(PROGMEM const uint8_t *image) {
		this->frame_fixed_repeat(0xaa, EPD_compensate);
		this->frame_fixed_repeat(0xaa, EPD_white);
		this->frame_data_repeat(image, EPD_inverse);
		this->frame_data_repeat(image, EPD_normal);
	}
```
To frame_fixed_repeat in EPD_V231_G2.cpp, where it's called "Fixed_value":
```
void EPD_Class::frame_fixed_repeat(uint8_t fixed_value, EPD_stage stage) {
```
Which actually just calls this:
```
// One frame of data is the number of lines * rows. For example:
// The 1.44” frame of data is 96 lines * 128 dots.
// The 2” frame of data is 96 lines * 200 dots.
// The 2.7” frame of data is 176 lines * 264 dots.

// the image is arranged by line which matches the display size
// so smallest would have 96 * 32 bytes

void EPD_Class::frame_data(PROGMEM const uint8_t *image, EPD_stage stage){
	for (uint8_t line = 0; line < this->lines_per_display ; ++line) {
		this->line(line, &image[line * this->bytes_per_line], 0, true, stage);
	}
}
```

That bit of code loops the number of lines in the display. The code that reads in lines looks like this:
```
// output one line of scan and data bytes to the display
void EPD_Class::line(uint16_t line, const uint8_t *data, uint8_t fixed_value, bool read_progmem, EPD_stage stage) {
```
Note that line is the line #, data is a pointer to the image, indexed in based on the line number, fixed_value is zero, read_progmem is true, not sure what stage is.
```
..........
if (this->middle_scan) { // true for EPD_1_44 and 2_0, false for EPD_1_9 and 2_6.
    // data bytes
    //Serial.println("odd pixels in middle scan...");
    this->odd_pixels(data, fixed_value, read_progmem, stage);

    // scan line
    for (uint16_t b = this->bytes_per_scan; b > 0; --b) { // bytes_per_scan = 96/4 = 24
	uint8_t n = 0x00;
	if (line / 4 == b - 1) {                         // 
		n = 0x03 << (2 * (line & 0x03));
	}
	SPI_put(n);
    }
.....
```
Note that data is the pointer to the image, fixed_val is zero, and line is just the line # of the current line we're looking at. I THINK SPI_put just basically does a new line or flushes the buffer or something. So the part of the code that actually matters is odd_pixels:

```
// pixels on display are numbered from 1 so odd is actually bits 0,2,4,...
void EPD_Class::odd_pixels(const uint8_t *data, uint8_t fixed_value, bool read_progmem, EPD_stage stage) {
```
data is the pointer to the image, fixed_value is 0, read_progmem is true, stage is ?
```
...
for (uint16_t b = this->bytes_per_line; b > 0; --b) { // loops over all the bytes in a line.
...
// AVR has multiple memory spaces
uint8_t pixels;
if (read_progmem) {                                       // this is true, so the image is stored in progmem??
    pixels = pgm_read_byte_near(data + b- 1) & 0x55;
} else {
    pixels = data[b - 1] & 0x55;                          
}
...
```
Info about progmem: Flash (program) memory (can store data here instead of SRAM).
I COULD HAVE REALIZED THIS FROM THE FACT THAT the image byte always is labeled PROGMEM LOL.
From [Arduino docs](https://www.arduino.cc/reference/en/language/variables/utilities/progmem/): 
- "While PROGMEM could be used on a single variable, it is really only worth the fuss if you have a larger block of data that needs to be stored, which is usually easiest in an array.
- "Using PROGMEM is also a two-step procedure. After getting the data into Flash memory, it requires special methods (functions), also defined in the pgmspace.h library, to read the data from program memory back into SRAM, so we can do something useful with it." This is the "pgm_read_byte_near" method above.

Later there's a switch statement and the part that uploads the image is:
```
case EPD_normal:       // B -> B, W -> W (New Image)
    pixels = 0xaa | pixels;
    break;
```

[More info](http://playground.arduino.cc/Learning/Memory) about different Arduino memory spaces:
- Flash memory (program space), is where the Arduino sketch is stored.
- SRAM (static random access memory) is where the sketch creates and manipulates variables when it runs.
- EEPROM is memory space that programmers can use to store long-term information.
- Flash memory and EEPROM memory are non-volatile (the information persists after the power is turned off). SRAM is volatile and will be lost when the power is cycled.
- Flash (PROGMEM) memory can only be populated at program burn time. You can’t change the values in the flash after the program has started running.

| Info | ATMega328p | MSP430 **G2553** IPW20R | Mega | AtTiny85| [MSP430**F5529**](http://www.ti.com/lit/ug/slau533d/slau533d.pdf) | 
|:--- | :---|:---|:---|:---|:---|
Flash | 32 kBytes (1 kByte used for bootloader) | 16KB | 256 kBytes (1 kByte used for bootloader) |8000 bytes|128Kbytes|
| SRAM | 2048 Bytes| ? | 8000 Bytes | 256 bytes | 8000 bytes |
| EEPROM | 1024 Bytes | ? | 4000 Bytes | 512 bytes | ? |
| RAM | ? | 512 Bytes | ? | - | - |
| Memory | ? | 2000 Bytes | ? | - | - |
| Power | ? | ? | ? | ? | 1.8-V to 3.6-V operation |


[More about MSP430 flash](http://www.ti.com/lit/ds/symlink/msp430g2553.pdf):

- The flash memory can be programmed via the Spy-Bi-Wire/JTAG port or in-system by the CPU. The CPU can
perform single-byte and single-word writes to the flash memory. Features of the flash memory include:
- Flash memory has n (**what is n?**) segments of main memory and four segments of information memory (A to D) of
64 bytes each. Each segment in main memory is 512 bytes in size.
- Segments 0 to n may be erased in one step, or each segment may be individually erased.
- Segments A to D can be erased individually or as a group with segments 0 to n. Segments A to D are also
called information memory.
- Segment A contains calibration data. After reset segment A is protected against programming and erasing. It
can be unlocked but care should be taken not to erase this segment if the device-specific calibration data is
required.

Note the cat_2_0 image is 15,094 bytes (16 KB on disk). So it's burned into flash, then loaded line by line into SRAM and sent to the epaper display.

Could send it over in SRAM-sized chunks, let's assume best-case and can use the entire SRAM:
15,094 / 2028 = 7.44 chunks. Could buy [this from Sparkfun](https://www.sparkfun.com/products/525) to increase size of EEPROM to 32kB (3200 Byte) of non volatile memory. Library to manage external memory: http://forum.arduino.cc/index.php?topic=502117.0

Writing that to the EPD sounds reallllly complicated tho...

**Image compression information**
- The four different approaches[3],[5] to compression are 
    - Statistical Compression, 
    - Spatial compression, 
    - Quantizing compression, 
    - Fractal compression. 
    - [src](https://arxiv.org/pdf/1112.2261.pdf)
- Run-length encoding (RLE) is a very simple form of data compression in which runs of data (that
is, sequences in which the same data value occurs in many consecutive data elements) are stored
as a single data value and count, rather than as the original run. This is most useful on data that
contains many such runs: for example, simple graphic images[8] such as icons, line drawings, and
animations.
- Huffman coding removes coding redundancy. Huffman’s procedure creates the
optimal code for a set of symbols and probabilities subject to the constraint that the symbols be
coded one at a time. After the code has been created, coding and/or decoding is accomplished in
the simple look-up table . When large number of symbols is to be coded, the construction of the
optimal binary Huffman code is a difficult task.

**Weird idea:**
Store a bunch of "image primitives" that you can reference when constructing a new image. As long as the instructions to reconstruct an image from the primitives are smaller than the image themselves would be, this would actually save you some space.

**Other memory and compression alg notes**

- The arduino is a Harvard architecture in which the instructions and data are in separate memory spaces.  It cannot execute an instruction stored in the RAM.  So you can't read a compiled sketch from an SD card into RAM and then start executing it. [src](https://forum.arduino.cc/index.php?topic=126230.0)
- Bitlash: http://bitlash.net/bitlash-users-guide.pdf
    - BITLASH INTERPRETER
        1. Runs in under 16kB on the AVR '328
        2. Parses Bitlash code on the fly from RAM, PROGMEM, EEPROM, or SD card
        3. Executes commands live from the command line and runs background tasks
    - Bitlash 2.0 (http://bitlash.net) can run script from SD card.  Your application can be as big as you like. The sample sketch that does this can be found here: https://github.com/billroy/bitlash/blob/master/examples/bitlashsd/bitlashsd.pde
    - 
    
#### 16 July 2018
**TODO**
- ~~Look at the partial update code for etc from nxp.~~ Will need to figure out how to use TI LaunchPad stuff before I can try that.
- Check Adafruit forum post re: Arduino image handling questions: https://forums.adafruit.com/viewtopic.php?f=19&t=138304
- Look into compressing .xbm? 
  - https://stackoverflow.com/questions/8417034/how-to-make-bitmap-compress-without-change-the-bitmap-size
  - https://android--code.blogspot.com/2015/09/android-how-to-compress-bitmap.html
- Send MIME data format instead? (Look up android way to do this).
- Send an .xbm of size Tag maxsize=820 bytes?

**Notes:**
- Reading image over nfc: How about if I just send the image file exactly as is, and just change what the file points to in arduino code?
  - Tried that, got this error message:  ```E/BrcmNfcNfa: Unable to write NDEF. Tag maxsize=820, request write size=15118 ```
  - From the NXP NFC tag datasheet:
      -  EEPROM is a non volatile memory that stores 1904 bytes user data (888 byte user data in case of the NTAG I2C 1k version).
      - I'm guessing we have the 1k version?
      - Sec. 8.3.9 says: "Pages 04h to E1h via the RF interface - Block 01h to 37h, plus the first 8 bytes of block 38h via the I2C interface are the user memory read/write areas for NTAG I2C 1k version."
 - Trying MIME type data format?
   - https://tools.ietf.org/html/rfc2045
   - Multipurpose Internet Mail Extensions, or MIME, redefines the format of messages to allow for **(1)** textual message bodies in character sets other than US-ASCII, **(2) an extensible set of different formats for non-textual message bodies**,  **(3) multi-part message bodies**, and (4) textual header information in character sets other than US-ASCII.


#### 13 July 2018
**TODO**
- Bitmap via NFC: looks like I need to send the bits over...*what is getting sent over now?*. Added a new arduino file: read-img-from-nfc to start to see what the file looks like. Seems like I'll need to send it over in the format? Many questions abound here.
- figure out if I can use [GFX](https://learn.adafruit.com/adafruit-gfx-graphics-library) on the MSP430
- Look at partial update code from NXP: https://github.com/molecule/AlterWear/blob/master/e-ink/EPD%20extension%20board%20for%20partial%20update%20v1.0_beta.rar
- ~~prettify/customize the app~~ (Renamed it, added launch icon) (will need more updating later but need to decide on interactions first).

**Notes**
- memory map: Still haven't found good docs, but experiments (and Christie) confirm NFC and I2C read from/to the same spot in memory (in other words I can write via NFC and read it via I2C). Haven't tried the reverse, but should be fine.
- Android app: switched over to the example from codexpedia since it is sooo much simpler. Brought the "dialog box" way of updating an NFC tag because the UX is so much better. Frankenstein is pretty good. New code: https://github.com/molecule/android_nfc_read_write
- Info about how the code goes through the images.
```
  case EPD_2_0: {
  this->lines_per_display = 96;
		this->dots_per_line = 200;
		this->bytes_per_line = 200 / 8;
		this->bytes_per_scan = 96 / 4;
  ```
- There are 96 lines per display for 2.0. Each line has 200/8=25 bytes, so that's 25 * 96 = 2400 bytes just in the image part. ~~So reading 1000 bytes might get me somewhere.~~ It didn't....the bits that I'm printing out dont' seem to match the bits I see in the cat_2_0.xbm file at all. I assume it's a printing issue....
- This might be useful at some point: Display bitmap in Android: https://stackoverflow.com/questions/4929989/how-to-display-bitmap-image-in-android
- I should get the teeniest xbm file, see what it looks like in bits, and see if I can send it over nfc.
  - Useful: https://stackoverflow.com/questions/15941643/nfc-send-image-jpeg
  - Useful: https://developer.android.com/training/beam-files/send-files
- But the arduino code just references the name "IMAGE_X_FILE_BITS" - so reading the bits directly wouldn't be the right thing. There must be somehwere where they actually use the .xbm file format....**Q:** where is that?
   - arduino printing out bits starting at ImAGE_1_BITS seems to be...gibberish?

#### July 9 2018
**TODO**
- try sending over a simple bitmap, and loading it from memory in Arduino code (as opposed to compiling it in).
- figure out memory map: get good docs
- figure out if I can use [GFX](https://learn.adafruit.com/adafruit-gfx-graphics-library) on the MSP430

**Notes**
- Reading from the NFC works via Android. Basically, you capture the intent and automatically do a read whenever you write. Specifically, this line:

```
record.setText(new String(message.getRecords()[0].getPayload(), "UTF-8"));
```

Displays whatever was last written to the NFC tag. (That line is called just before I write, so the basic interaction with an NFC tag automatically reads it. (THere are probably ways to encrypt or hide stuff, but this is fine for now).
- This app will also successfully read: https://github.com/codexpedia/android_nfc_read_write
- eink/i2c-basic-test seems to be reading from memory somewhere. I need to read the docs to understand where, and would ideally like to confirm that it contains what I sent over "Sell your cleverness and buy bewilderment".

- **Q:** Where is it reading FROM?
   - [This code from the codexpedia example](https://github.com/codexpedia/android_nfc_read_write/blob/master/app/src/main/java/com/example/peng/nfcreadwrite/MainActivity.java#L89) seems to imply it's automatically bundled in an "NdefRecord" that gets sent when an NFC tag is activated.
   - [This article by Shane Tully](https://shanetully.com/2012/12/writing-custom-data-to-nfc-tags-with-android-example/) further confirms that you capture an intent when the tag is activated, and can immediately read and write.
- **Q2:** What is the actual memory layout of the NFC, and how does that interact with I2C and NFC?
   - All links to docs I've found are giving [404 page not found errors](https://github.com/repaper/gratis/issues/78) :(
  
Printout from eink/i2c-basic-test (after loading "sell your cleverness and buy bewilderment":
```
i: 10, desired_state: 83
i: 11, byte: 101              e
i: 12, byte: 108              l
i: 13, byte: 108              l
i: 14, byte: 32               [space]
i: 15, byte: 121              y
i: 16, byte: 111              o

```
  - BOOM: Ok, so NFC and I2C are certainly reading from the same memory space, starting at address: ```#define int_reg_addr 0x01      //first block of user memory``` Next I need to try sending over a simple bitmap, and loading it from there in Arduino code.

- **Q3:** What about partial update?
   - This seems to be all done in SW. See video demos [here](https://www.youtube.com/watch?v=enzUbiSWenQ) and [here.](https://github.com/repaper/gratis#fast-update-notes-july-2017)
   - [Rumor](https://github.com/repaper/gratis/issues/48) has it that Adafruit's GFX library also does it. (as well as [text](https://github.com/repaper/gratis/issues/46))
        - More info about the GFX lib [here](https://learn.adafruit.com/adafruit-gfx-graphics-library)
- **Q4:** Can I use GFX on the MSP430?
   - The GFX lib "require 2 complete frame-buffers to update the display from SRAM." [[src](https://learn.adafruit.com/repaper-eink-development-board/libraries-and-examples)]


#### July 5 2018
**TODO**
- ~~read: https://shanetully.com/2012/12/writing-custom-data-to-nfc-tags-with-android-example/~~
- App changes
  - ~~Upload to my phone~~
  - ~~Add ability to send more data (up to 10MB?)~~ - At least can send a full sentence now. Need to try w bitmaps eventually.
  - Try to send a simple pic.

#### July 3 2018
- Take out lines from lib code:
```
this->frame_fixed_repeat(0xaa, EPD_compensate); // changes nothing obvious, at least w/ 4 image switches.
this->frame_fixed_repeat(0xaa, EPD_white); // changes nothing obvious, w/ 4 image switches.
this->frame_data_repeat(image, EPD_inverse); // Didn't "do inverse of image", image seems darker (need to compare w/ orig video)
this->frame_data_repeat(image, EPD_normal);
```
Next: need to try actually timing.

- Learning about NDEF Messages ([source](https://android.googlesource.com/platform/frameworks/base/+/master/core/java/android/nfc/NdefMessage.java)), and NDEF Records ([source](https://android.googlesource.com/platform/frameworks/base/+/master/core/java/android/nfc/NdefRecord.java)
```
An NDEF Record contains typed data, such as MIME-type media, a URI, or a custom application payload. An NDEF Message is a container for one or more NDEF Records.
 ```
 ```
 An NDEF Message contains one or more NDEF Records.
 ```
 ```
 public static NdefRecord createMime(String mimeType, byte[] mimeData) {
 Create a new NDEF Record containing MIME data. Use this method to encode MIME-typed data into an NDEF Record, such as "text/plain", or "image/jpeg".
 ```
 Relevant? 
 ``` 
 private static final int MAX_PAYLOAD_SIZE = 10 * (1 << 20);  // 10 MB payload limit
 ```

#### July 2 2018
- Pro mini janks up my USB ports: too annoying to work with since I have to continually restart.
- Uno works well, reads NFC fine.
- How big are my current images? Does the code currently store all of them on the Uno? Where exactly? What's the capacity? What's the transfer time?
- Would there be a way to do a "diff" of two images, and only redraw the "different" pixels? Could use less memory.
- ~~Can I run the Uno off the NFC power? (almost def note but should try it).~~ --> NO.
