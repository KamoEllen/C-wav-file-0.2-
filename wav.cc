#include <iostream>
#include <fstream>

// The sample rate of the WAV file (in samples per second)
const int SAMPLE_RATE = 44100;

// The number of channels in the WAV file (1 for mono, 2 for stereo)
const int NUM_CHANNELS = 1;

// The number of bits per sample in the WAV file (8 or 16)
const int BITS_PER_SAMPLE = 16;

int main() {
  // Create a vector to hold the samples for the WAV file
  std::vector<int16_t> samples;

  // Generate some example samples (a simple sine wave)
  for (int i = 0; i < SAMPLE_RATE; i++) {
    float t = (float)i / SAMPLE_RATE;
    float sample = 32767 * sin(2 * M_PI * 440 * t);
    samples.push_back((int16_t)sample);
  }

  // Open the output file for writing
  std::ofstream out("example.wav", std::ios::binary);

  // Write the RIFF header
  out.write("RIFF", 4);
  uint32_t file_size = 36 + samples.size() * sizeof(int16_t);
  out.write((const char*)&file_size, 4);
  out.write("WAVE", 4);

  // Write the format chunk
  out.write("fmt ", 4);
  uint32_t chunk_size = 16;
  out.write((const char*)&chunk_size, 4);
  uint16_t audio_format = 1;
  out.write((const char*)&audio_format, 2);
  out.write((const char*)&NUM_CHANNELS, 2);
  out.write((const char*)&SAMPLE_RATE, 4);
  uint32_t byte_rate = SAMPLE_RATE * NUM_CHANNELS * BITS_PER_SAMPLE / 8;
  out.write((const char*)&byte_rate, 4);
  uint16_t block_align = NUM_CHANNELS * BITS_PER_SAMPLE / 8;
  out.write((const char*)&block_align, 2);
  out.write((const char*)&BITS_PER_SAMPLE, 2);

  // Write the data chunk
  out.write("data", 4);
  uint32_t data_size = samples.size() * sizeof(int16_t);
  out.write((const char*)&data_size, 4);
  out.write((const char*)samples.data(), data_size);

  // Close the output file
  out.close();

  return 0;
}
