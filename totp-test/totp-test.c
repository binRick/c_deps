////////////////////////////////////////////

////////////////////////////////////////////
#include "totp-test/totp-test.h"
////////////////////////////////////////////
#include "ansi-codes/ansi-codes.h"
#include "c_fsio/include/fsio.h"
#include "c_greatest/greatest/greatest.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "libmutotp/base32codec.h"
#include "libmutotp/sha1.h"
#include "libmutotp/totp.h"
#include "log/log.h"
#include "timestamp/timestamp.h"

int32_t FillFromURANDOM(uint8_t *out, size_t outlen){
  FILE *fpurandom = fopen("/dev/urandom", "r");

  if (!fpurandom)
    return(-1);


  int32_t bread = fread(out, 1, outlen, fpurandom);

  fclose(fpurandom);

  return(bread < outlen ? -1 : bread);
}

////////////////////////////////////////////
TEST t_totp_test(){
  char secret[33] = { 0 };

//Create a base32 encoded secret in an ascii string
  generate_random_secret(secret, 33, FillFromURANDOM);
  printf("Secret: %s\n", secret);

//Create an ANSI QR code graphic. The pointer on the line below owns its new heap memory.
  char *qrcodeansi = create_totp_qrcode("Test", "Meow", secret);

  printf("--------------------------------------------------------------------------------\n");
  printf("%s\n", qrcodeansi);

//Free the memory holding the ANSI QR code graphic
  free(qrcodeansi);

  char secret1[33] = { 0 };
  char buf[512]    = "XXXXXXXXXXXXx";

//In actual use, you would store the secret with the user's account instead of
//prompting for it, then retrieve it later when he logs in to validate his
//OTPs with.

//Decode the secret from base32 ASCII to its raw data
  size_t secretlen = base32decode(buf, strnlen(buf, 512), secret1, 33);

//Compute current TOTP using the entered secret and current time.
//The user's authenticator app will do the same calculation for them,
//and if both their app and this program agree (are time-synced and share
//the same secret), the user's OTP will match the one below.
  time_t now = time(0);
  int    otp = compute_totp(secret, secretlen, now, 30, 6);

  printf("Current otp code: %06d\n", otp);

  PASS();
}

SUITE(s_totp_test) {
  RUN_TEST(t_totp_test);
}

GREATEST_MAIN_DEFS();

int main(const int argc, const char **argv) {
  GREATEST_MAIN_BEGIN();
  RUN_SUITE(s_totp_test);
  GREATEST_MAIN_END();
}
