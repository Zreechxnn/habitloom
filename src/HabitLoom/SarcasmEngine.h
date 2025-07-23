#ifndef SARCASMENGINE_H
#define SARCASMENGINE_H

#include <QString>
#include <QStringList>
#include <random>
#include <ctime>

class SarcasmEngine
{
public:
    SarcasmEngine(bool brutalMode = false);

    QString getRewardMessage();
    QString getPunishmentMessage();
    QString getRandomNotification();
    void setBrutalMode(bool enabled) { brutalMode = enabled; }
    void setSarcasmLevel(int level) { sarcasmLevel = level; }

private:
    bool brutalMode;
    int sarcasmLevel = 2; // 1-3 scale
    std::mt19937 rng;

    const QStringList rewards = {
        "Selamat, kamu tidak menjadi beban negara hari ini",
        "Luar biasa! Mungkin besok kamu bisa lebih berguna",
        "Kamu berhasil! Sekarang coba lakukan tanpa disuruh",
        "Hebat! Jangan sampai kejadian dua kali ya"};

    const QStringList punishments = {
        "Oh, jadi kamu memilih menjadi makhluk rebahan lagi?",
        "Kegagalan hari ini: Kamu. Alasannya: Malas",
        "Besok janji ya? (Tapi kita tahu kenyataannya)",
        "Hidup ini pilihan. Kamu memilih untuk gagal"};

    const QStringList brutalRewards = {
        "Tidak percaya! Kamu benar-benar melakukan sesuatu yang produktif!",
        "Astaga! Mungkin ini tanda kiamat - kamu menyelesaikan tugas!",
        "Siapa kamu dan apa yang telah kamu lakukan dengan pemalasnya?",
        "Jika kamu terus begini, aku akan kehabisan bahan olokan"};

    const QStringList brutalPunishments = {
        "Keputusan terbaik hari ini: TIDUR! Karena bangun pun cuma jadi beban",
        "Kamu ini spesies apa? Tikus got lebih produktif!",
        "Mati saja lebih efisien daripada hidup seperti ini",
        "Kegagalanmu hari ini adalah warisan untuk anak cucumu"};

    const QStringList randomNotifications = {
        "Apakah kamu sedang bekerja atau hanya berpura-pura sibuk seperti DPR?",
        "Progressmu lebih lambat dari molases di kutub utara!",
        "Aktivitas terbaik hari ini: ngacroll IG?",
        "Masih hidup? Atau cuma ada di dunia maya?",
        "Kerja atau tidur? Pilih satu! (Tapi kita tahu jawabannya)"};
};

#endif // SARCASMENGINE_H