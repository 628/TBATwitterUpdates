#ifndef TBATWITTERUPDATES_XTBACHECKSUM_H
#define TBATWITTERUPDATES_XTBACHECKSUM_H

#include <string>
#include <pistache/http_header.h>

using namespace Pistache;

class XTBAChecksum : public Http::Header::Header {
public:
    NAME("X-TBA-Checksum");

    XTBAChecksum()
            : checkSum() {}

    void parse(const std::string &str) override {}

    void write(std::ostream &os) const override {}

    std::string getCheckSum() {
        return checkSum;
    }

private:
    std::string checkSum;
};


#endif //TBATWITTERUPDATES_XTBACHECKSUM_H
