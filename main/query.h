#ifndef QUERY_H
#define QUERY_H

#define A (htons(1))
#define NS (htons(2))
#define CNAME (htons(5))
#define SOA (htons(6))
#define MX (htons(15))
#define TXT (htons(16))
#define AAAA (htons(28))
#define RRSIG (htons(46))
#define NSEC  (htons(47))
#define DNSKEY  (htons(48))
#define NSEC3 (htons(50))
#define NSEC3PARAM (htons(0))

#define CLASS_IN    htons(0x0001)

struct dns_header {
    uint16_t id;
    /*The following 2 bytes have reversed endianess*/
    uint16_t rd_flag     :1; //recursion desired
    uint16_t tc_flag     :1; //truncated response
    uint16_t aa_flag     :1; //authorititive answer
    uint16_t opcode      :4;
    uint16_t answer_flag :1;

    uint16_t rcode       :4;
    uint16_t cd_flag     :1; //checking disabled
    uint16_t ad_flag     :1; //authenticated data
    uint16_t z_flag      :1; //reserved
    uint16_t ra_flag     :1; //recursion enabled

    uint16_t qr_count;
    uint16_t an_count;
    uint16_t au_count;
    uint16_t ad_count;
};

char *
query_decompress_rdata(char *buf, int buflen, char *owner_end);

void
query_to_formerr(char *buf);

void
query_to_nxdomain(char *buf);

char *
query_axfr_msg(char *qhdr, char *query, int tcp, size_t *s);

int
query_find_owner_uncompressed(char *start, char **end, char *bufend);

size_t
query_reply_from_rrset(char *query, size_t qlen, char *payload, char *answer, size_t alen,
    char **rr, size_t rr_count, char *rrsig);

int
query_read_rr(char *buf, char *bufend, char **owner_end, uint16_t **rdatalen, char **rdata);

uint16_t query_pkt_qr_count(char *buf);
uint16_t query_pkt_an_count(char *buf);
uint16_t query_pkt_au_count(char *buf);
uint16_t query_pkt_ad_count(char *buf);

char *
query_find_owner_compressed(char *pkt, size_t pktlen, char *start);

void
query_printname(char *name);

void
printx(char *buf, size_t len);

char *
query_axfr_rr(char *z);

#endif /*QUERY_H*/
