2024 June 16: version 0.1
I added a header row to data, and changed the verbosity to 2. I piped the screen output to screen.txt. ~~The frequency range from 0 to 1 Hz is below the human hearing threshold of 20 Hz. I might sweep the human hearing range in the next version. Note that w=2PIf, where w is omega, the angular frequency.~~

2024 June 22: note
Recall from chapter 3, Sampling and Quantizing, that that frequencies equal each other modulo N, hence the Nyquist frequency.

2024 June 23: note
f = (k/N)*f_s where f_s is the sample rate

What is the sample rate if we are generating a signal? Use the abstraction f_s instead because we are not sampling and hence do not have a specific sampling rate. This makes more sense than a range of 0 to 1 Hz
