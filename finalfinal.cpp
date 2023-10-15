#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//deklarasi global
typedef char string[50];
int cekData=0;   //untuk mengecek data sudah terisi atau belum
int cekNilai=0;  //untuk mengecek data sudah terisi atau belum

// function yang digunakan
void datasiswa();
void nilaisiswa();
void cetaklaporan();
void sortingAkhir(struct siswa data[], int i);
void swap(struct siswa *a, struct siswa *b);
void TampilData(struct siswa data[], int i);
void caridatasiswa();
int search(struct siswa data[], int i, string cariid);

//isi variabel yang akan dimuat dalam program
struct siswa{
	string id;
	string nama;
	string jeniskursus;
	int quiz;
	int tugas;
	int ujian;
	int akhir;
	char grade;
}data;

int main(){
	int pilih;
	do{ 
		printf("~Selamat datang dalam program English Course~\n\n");
		//menu utama
		printf("Silahkan pilih menu:\n");
		printf("1. Masukkan data siswa.\n");
		printf("2. Masukkan nilai siswa.\n");
		printf("3. Cetak laporan siswa.\n");
		printf("4. Sorting laporan siswa.\n");
		printf("5. Cari data siswa.\n");
		printf("0. keluar.\n");
		printf("Pilihan: ");
	
		scanf("%d",&pilih);
		
		switch(pilih){
			case 1: 
				datasiswa();  //memanggil void datasiswa()
				break;
			case 2: 
				nilaisiswa();  //memanggil void nilaisiswa()
				break;
			case 3: 
				if(cekData==1&&cekNilai==1){
					cetaklaporan();  //memanggil void cetaklaporan()
				}else{
					printf("Silakan lengkapi data terlebih dahulu!!!!\n\n");
				}
				break;
			case 4 :
				struct siswa data[100];
				int i;
				FILE *fp_sort;
				fp_sort=fopen("DataSiswa.txt","r");  //membaca file DataSiswa.txt
				while(fscanf(fp_sort,"Nomor Registrasi Siswa: %s\nNama: %s\nJenis kursus: %s\nNilai quiz: %d\nNilai tugas: %d\nNilai ujian: %d\nNilai akhir: %d\nGrade: %c\n-------------------------------------------\n\n",
				&data[i].id,&data[i].nama,&data[i].jeniskursus,&data[i].quiz,&data[i].tugas,&data[i].ujian,&data[i].akhir,&data[i].grade)!=EOF){
					i++;  //data dimasukkan ke dalam array
				}
				fclose(fp_sort);
				sortingAkhir(data,i);  //memanggil void sortingAkhir()
				TampilData(data,i);  //memanggil void TampilData()
				break;
			case 5: 
				caridatasiswa(); //memanggil void caridatasiswa()
				break;		
			case 0 :
				printf("Terima Kasih!\n\n");
				break;
			default : 
				printf("Input salah! Silahkan masukkan input yang benar.\n");
				break;
		}
		system("pause");  //untuk menahan program agar user dapat melihat data yang ditampilkan sebelumnya
		system("cls");  //untuk clearscreen sebelum memasukkan menu lainnya
	}while(pilih!=0);
	return 0;
}

void datasiswa(){  //function untuk menginput data siswa
	struct siswa temp[100];
	int i;
	FILE *fp_search;
	fp_search=fopen("DataSiswa.txt","r");
	while(fscanf(fp_search,"Nomor Registrasi Siswa: %s\nNama: %s\nJenis kursus: %s\nNilai quiz: %d\nNilai tugas: %d\nNilai ujian: %d\nNilai akhir: %d\nGrade: %c\n-------------------------------------------\n\n",&temp[i].id,&temp[i].nama,&temp[i].jeniskursus,&temp[i].quiz,&temp[i].tugas,&temp[i].ujian,&temp[i].akhir,&temp[i].grade)!=EOF){
		i++;
	}	
	fclose(fp_search);
	
	printf("Nomor Registrasi Siswa: ");
	fflush(stdin); gets(data.id);
	
	for(i=0;i<100;i++){  //untuk mengecek apakah id siswa sudah pernah terdaftar atau belum
		if(strcmp(temp[i].id, data.id)==0){
			printf("\nNomor Registrasi sudah ada silakan input ulang\n");
			return;
		}
	}
	
	printf("Nama: ");
	fflush(stdin); gets(data.nama);
	
	printf("Jenis kursus (Beginner/Intermediate/Advance): ");
	fflush(stdin); gets(data.jeniskursus);

	printf("\n");
	printf("Input data berhasil\n\n");
	cekData = 1;  //menandakan bahwa data telah terisi
}

void nilaisiswa(){  //function untuk menginput nilai siswa
	printf("Nilai quiz: ");
	scanf("%d",&data.quiz);
	printf("Nilai tugas: ");
	scanf("%d",&data.tugas);
	printf("Nilai ujian: ");
	scanf("%d",&data.ujian);
	
	data.akhir=(0.3*data.quiz)+(0.3*data.tugas)+(0.4*data.ujian);  //menghitung nilai akhir
	printf("Nilai akhir: %d\n",data.akhir);
	//menentukan grade
	if(data.akhir>=85){
		data.grade='A';	
	}
	else if(data.akhir<85&&data.akhir>=70){
			data.grade='B';
	}
	else if(data.akhir<70&&data.akhir>=60){
			data.grade='C';
	}
	else if(data.akhir<60&&data.akhir>=50){
			data.grade='D';
	}
	else{
			data.grade='E';
	}
	printf("\n");
	printf("Input nilai berhasil\n\n");
	cekNilai = 1; //menandakan bahwa data telah terisi
}


void cetaklaporan(){  //untuk mencetak data dari array program ke dalam file
	FILE *fp;
	fp=fopen("DataSiswa.txt","a");
	printf("\nMencetak file...\n\n");
	printf("Nomor Registrasi Siswa: %s\n",data.id);
	printf("Nama: %s\n",data.nama);
	printf("Jenis Kursus: %s\n",data.jeniskursus);
	printf("Nilai quiz: %d\n",data.quiz);
	printf("Nilai tugas: %d\n",data.tugas);
	printf("Nilai ujian: %d\n",data.ujian);
	printf("Nilai akhir: %d\n",data.akhir);
	printf("Grade: %c\n",data.grade);
	printf("------------------------------------------\n\n");
	fprintf(fp,"Nomor Registrasi Siswa: %s\n",data.id);
	fprintf(fp,"Nama: %s\n",data.nama);
	fprintf(fp,"Jenis kursus: %s\n",data.jeniskursus);
	fprintf(fp,"Nilai quiz: %d\n",data.quiz);
	fprintf(fp,"Nilai tugas: %d\n",data.tugas);
	fprintf(fp,"Nilai ujian: %d\n",data.ujian);
	fprintf(fp,"Nilai akhir: %d\n",data.akhir);
	fprintf(fp,"Grade: %c\n",data.grade);
	fprintf(fp,"-------------------------------------------\n\n");
	printf("\nMencetak file selesai!!!!!\n\n");
	fclose(fp);
}

void sortingAkhir(struct siswa data[], int i){  //untuk mengurutkan data dari nilai akhir yang terkecil ke terbesar
	int j, k, idx_low;
    for (j = 0;  j < i - 1;  j++) {
        idx_low = j;
        for (k = j + 1; k < i; k++) 
			if (data[idx_low].akhir > data[k].akhir) idx_low = k;
			if (idx_low > j) swap(&data[j], &data[idx_low]);
    }
}
	

void swap(struct siswa *a, struct siswa *b){  //untuk menukar data
	struct siswa temp;
	strcpy(temp.id, a->id);  // menggunakan tanda -> karena menggunakan pointer
	strcpy(temp.nama, a->nama);
	strcpy(temp.jeniskursus, a->jeniskursus);
	temp.quiz = a->quiz;
	temp.tugas = a->tugas;
	temp.ujian = a->ujian;
	temp.akhir = a->akhir;
	temp.grade = a->grade;
	
	strcpy(a->id, b->id);
	strcpy(a->nama, b->nama);
	strcpy(a->jeniskursus, b->jeniskursus);
	a->quiz = b->quiz;
	a->tugas = b->tugas;
	a->ujian = b->ujian;
	a->akhir = b->akhir;
	a->grade = b->grade;
	
	strcpy(b->id, temp.id);
	strcpy(b->nama, temp.nama);
	strcpy(a->jeniskursus, temp.jeniskursus);
	b->quiz = temp.quiz;
	b->tugas = temp.tugas;
	b->ujian = temp.ujian;
	b->akhir = temp.akhir;
	b->grade = temp.grade;
}

void TampilData(struct siswa data[], int i){  //untuk menampilkan data ke layar
	for(int j=0; j<i; j++){
		printf("Nomor Registrasi Siswa: %s\n",data[j].id);
		printf("Nama: %s\n",data[j].nama);
		printf("Jenis Kursus: %s\n",data[j].jeniskursus);
		printf("Nilai quiz: %d\n",data[j].quiz);
		printf("Nilai tugas: %d\n",data[j].tugas);
		printf("Nilai ujian: %d\n",data[j].ujian);
		printf("Nilai akhir: %d\n",data[j].akhir);
		printf("Grade: %c\n",data[j].grade);
		printf("------------------------------------------\n\n");
	}
}

int search(struct siswa data[], int i, string cariid){  //untuk mencari id siswa yang cocok
	int j;
	for(j=0;j<i;j++){
		if(strcmp(data[j].id,cariid)==0){
			return j;
		}
	}
	return -1;
}

void caridatasiswa(){  //untuk mencari dan menampilkan data siswa yang dicari berdasarkan id
	struct siswa data[100];
	int i,index;
	string cariid;
	FILE *fp_cari;
	fp_cari=fopen("DataSiswa.txt","r");
	while(fscanf(fp_cari,"Nomor Registrasi Siswa: %s\nNama: %s\nJenis kursus: %s\nNilai quiz: %d\nNilai tugas: %d\nNilai ujian: %d\nNilai akhir: %d\nGrade: %c\n-------------------------------------------\n\n",&data[i].id,&data[i].nama,&data[i].jeniskursus,&data[i].quiz,&data[i].tugas,&data[i].ujian,&data[i].akhir,&data[i].grade)!=EOF){
		i++;
	}
	printf("Masukkan id siswa: ");
	fflush(stdin); gets(cariid);
	index=search(data,i,cariid);//i banyaknya array dari struct siswa data
	if(index!=-1){
		printf("Nomor Registrasi Siswa: %s\n",data[index].id);
		printf("Nama: %s\n",data[index].nama);
		printf("Jenis Kursus: %s\n",data[index].jeniskursus);
		printf("Nilai quiz: %d\n",data[index].quiz);
		printf("Nilai tugas: %d\n",data[index].tugas);
		printf("Nilai ujian: %d\n",data[index].ujian);
		printf("Nilai akhir: %d\n",data[index].akhir);
		printf("Grade: %c\n",data[index].grade);
	}
	else{
		printf("Data tidak ditemukan.\n");
	}
	fclose(fp_cari);
}

