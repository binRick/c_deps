////////////////////////////////////////////

////////////////////////////////////////////
#include "sigstr-test/sigstr-test.h"
////////////////////////////////////////////
#include "ansi-codes/ansi-codes.h"
#include "c_fsio/include/fsio.h"
#include "c_greatest/greatest/greatest.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "log/log.h"
#include "sigstr/wifi_helper.h"
#include "timestamp/timestamp.h"

////////////////////////////////////////////

/*
 * void print_wifi_info()
 * {
 * char ssid[0x100] = {'\0'};
 * sprintf(ssid, "%s", wh_get_ssid());
 *
 * char mac_addr[0x100] = {'\0'};
 * sprintf(mac_addr, "%s", wh_get_mac());
 *
 * char country[0x100] = {'\0'};
 * sprintf(country, "%s", wh_get_country());
 *
 * char iname[0x100] = {'\0'};
 * sprintf(iname, "%s", wh_get_iface_name());
 *
 * int rssi = wh_get_rssi();
 * enum wh_wifi_mode mode = wh_get_mode();
 * int noise = wh_get_noise();
 * int tpwr = wh_get_transmit_pwr();
 * int channel = wh_get_channel();
 * double trate = wh_get_transmit_rate();
 *
 * printf(
 *  "%-15s %s\n",
 *  "ssid:", ssid
 * );
 * printf(
 *  "%-15s %s%d%s dBm\n",
 *  "rssi:", wh_rssi_ansi_prefix(rssi), rssi, ANSI_END
 * );
 * printf(
 *  "%-15s %s%d%s dBm\n",
 *  "noise:", wh_noise_ansi_prefix(noise), noise,ANSI_END
 * );
 * printf(
 *  "%-15s %d mW\n",
 *  "transmit power:", tpwr
 * );
 * printf(
 *  "%-15s %0.2lf Mbps (%d max)\n",
 *  "transmit rate:", trate,
 *  wh_mode_max_rate(mode)
 * );
 *    printf(
 *    "%-15s %d\n",
 *    "channel:", channel
 *  );
 *  printf(
 *    "%-15s %s\n",
 *    "iface name:", iname
 *  );
 *  printf(
 *    "%-15s %s\n",
 *    "mode:", wh_mode_string(mode)
 *  );
 *  printf(
 *    "%-15s %s\n",
 *    "mac addr:", mac_addr
 *  );
 *  printf(
 *    "%-15s %s\n",
 *    "country:", country
 *  );
 * }
 */
TEST t_sigstr_test(){
//print_wifi_info();
  PASS();
}

SUITE(s_sigstr_test) {
  RUN_TEST(t_sigstr_test);
}

GREATEST_MAIN_DEFS();

int main(const int argc, const char **argv) {
  GREATEST_MAIN_BEGIN();
  RUN_SUITE(s_sigstr_test);
  GREATEST_MAIN_END();
}
