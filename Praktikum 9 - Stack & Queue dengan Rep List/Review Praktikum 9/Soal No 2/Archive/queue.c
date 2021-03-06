/* Nama/ NIM		: Dharma Kurnia Septialoka/ 13514028
 * Nama file		: queue.c
 * Topik		    : ADT QUEUE
 * Tanggal		    : 3 November 2015
 * Deskripsi		: List linier queue
*/

#include "queue.h"

/** Konstruktor/Kreator **/
void CreateEmpty (Queue *Q) {
	Head(*Q)= Nil;
	Tail(*Q)= Nil;
}
/*	I.S. sembarang
	F.S. Sebuah Q kosong terbentuk
*/

/* Prototype manajemen memori */
void Alokasi (Address *P, Infotype X) {
	*P= (ElmtQueue *) malloc (sizeof(ElmtQueue));
	if (*P!= Nil) {
		Info(*P)= X;
		Next(*P)= Nil;
	}
}
/*	I.S. P sembarang, X terdefinisi
	F.S. Alamat P dialokasi, jika berhasil maka Info(P) = X dan Next(P) = Nil
	P = Nil jika alokasi gagal
*/

void Dealokasi (Address *P) {
	free(*P);
	*P= Nil;
}
/*	I.S. P adalah hasil alokasi, P <> Nil
	F.S. Alamat P didealokasi, dikembalikan ke sistem
*/


/* Predikat Pemeriksaan Kondisi Queue */
boolean IsEmpty (Queue Q) {
	if (Head(Q) == Nil && Tail(Q) == Nil) {
		return true;
	} else {
		return false;
	}
}
/*	Mengirim true jika Q kosong: HEAD(Q) = Nil and TAIL(Q) = Nil */

int NbElmt (Queue Q) {
	Address P;
	int nb;

	if (IsEmpty(Q)) {
		return 0;
	} else {
		P= Head(Q);
		nb= 1;
		while(P!= Tail(Q)) {
			nb++;
			P= Next(P);
		}
		return nb;
	}
}
/*	Mengirimkan banyaknya elemen queue. Mengirimkan 0 jika Q kosong. */

/*** Primitif Add/Delete **/

// A B C 
// Prec P Succ
void Add (Queue *Q, Infotype X) {
	Address P, Prec, Succ;
	boolean fail;
	int timer, timer1;
	Infotype A, B, C, T;

	Alokasi(&P, X);
	fail= false;
	if (P!= Nil) {
		if (IsEmpty(*Q)) {
			Head(*Q)= P;
			Tail(*Q)= P;
		} else {
			B= Info(P);
			if (NbElmt(*Q) == 1) {
				Next(Tail(*Q))= P;
				Tail(*Q)= P;
				A= Info(Head(*Q));
			} else {
				T= Info(Tail(*Q));
				timer= T.waktuKedatangan + T.mulaiPelayanan + T.lamaPelayanan;
				if (B.waktuKedatangan > timer) {
					Next(Tail(*Q))= P;
					Tail(*Q)= P;
					A= T;
				} else { //mau diselipin
					Prec= Head(*Q);
					Succ= Next(Prec);
					while(Prec!= Tail(*Q) && !fail) {
						A= Info(Prec);
						C= Info(Succ);
						if (C.mulaiPelayanan == 0) {
							Prec= Succ;
							Succ= Next(Succ);
						} else {
							timer1= A.lamaPelayanan + A.waktuKedatangan + A.mulaiPelayanan;
							if (B.waktuKedatangan > timer1) {
								Prec= Succ;
								Succ= Next(Succ);
							} else {
								if (B.nilaiMath <= C.nilaiMath) {
									Prec= Succ; 
									Succ= Next(Succ);
								} else {
									fail= true;
								}
							}
						}
					}

					if (Prec == Tail(*Q)) {
						A= Info(Tail(*Q));
						Next(Tail(*Q))= P;
						Tail(*Q)= P;
					} else { //fail= true
						Next(P)= Succ;
						Next(Prec)= P;
						A= Info(Prec);
					}

				}

			}
			B.mulaiPelayanan= A.waktuKedatangan - B.waktuKedatangan + A.mulaiPelayanan + A.lamaPelayanan;
			if (B.mulaiPelayanan <= 0) {
				B.mulaiPelayanan= 0;
			}
			Info(P)= B; //info P tadinya diassign ke B lalu B yg diubah-ubah, lalu dikembalikan lg ke info P
			while (P!= Tail(*Q)) {
				Prec= P;
				P= Next(P); 
				A= Info(Prec);
				B= Info(P);
				B.mulaiPelayanan= A.waktuKedatangan - B.waktuKedatangan + A.mulaiPelayanan + A.lamaPelayanan;
				if (B.mulaiPelayanan <= 0) {
					B.mulaiPelayanan= 0;
				}
				Info(P)= B;
			}
		}
	}
}
/*	Proses : Mengalokasi X dan menambahkan X pada bagian TAIL dari Q jika alokasi
	berhasil; jika alokasi gagal Q tetap
	I.S. Q mungkin kosong
	F.S. X menjadi TAIL, TAIL "maju"
*/

void Del (Queue *Q, Infotype *X) {
	Address P;

	*X= InfoHead(*Q);
	P= Head(*Q);

	if (Next(P) == Nil) {
		Head(*Q)= Nil;
		Tail(*Q)= Nil;
	} else {
		Head(*Q)= Next(P);
	}
	Dealokasi(&P);
}
/*	Proses : Menghapus X pada bagian HEAD dari Q dan mendealokasi elemen HEAD
	I.S. Q tidak mungkin kosong
	F.S. X = nilai elemen HEAD pd I.S., HEAD "mundur"
*/

