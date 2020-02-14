const int RPM=4000;
const int sectors=12;
const int depth=6000; // field depyh in nanometers
const int section=300; // Nyquist slice in nm
const int slices=depth/section+1; // # of sections

const int ms_revolution=60000/RPM; // millisecond per turn
const int us_sector=(1000*ms_revolution)/sectors; // should be 1250 microseconds per sector

const int sectors2slice=12; // how many sectors to a single slice?
const int us_slice=sectors2slice*us_sector;

// total scan time is 21 slices, each lasting 12 sectors, i.e. 252 sectors total or 315ms

int levels[slices];

const float range_um=6.0; // must be smaller or equal 44 micron
int const rangei = floor(4095.9999*range_um/44.0);

const int dark=1000;


void setup() {
  analogWriteResolution(12);
  
  pinMode(2, OUTPUT);
  //pinMode( 8,INPUT_PULLUP);
  pinMode(DAC1, OUTPUT);
  analogWrite(DAC1,0);
  digitalWrite(2,0);

  for(int i=0; i<slices; i++) levels[i]=i*rangei/(slices-1);
  //digitalWrite(2, LOW); digitalWrite(3, LOW);digitalWrite(4, LOW);
}

int S=0;
void loop() {
  if(S>=slices) {
    S=0;
    // ramp down fast
    for(int i=rangei-1; i>=0; i--) {
      analogWrite(DAC1,i);
      delayMicroseconds(3);
    }
    delay(100);
  } else {
    analogWrite(DAC1,levels[S]);
    if(S==0) digitalWrite(2,1);
    delayMicroseconds(us_slice);
    if(S==0) digitalWrite(2,0);
    S++;
  }
}

