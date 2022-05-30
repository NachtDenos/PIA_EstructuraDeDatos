#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version = '6.0.0.0' processorArchitecture = '*' publicKeyToken = '6595b64144ccf1df' language = '*'\"")
//EDSON
#include <Windows.h>
#include "resource.h"
#include <string>
#include <fstream>
#include <wchar.h>
#include <time.h>
#pragma warning (disable:4996)
#define TIMER_GENERICO 700
using namespace std;

#pragma region ESTRUCTURAS
struct User {
	int idUser;
	string clave;
	string password;
	string apUser;
	string amUser;
	string nameUser;
	User* nextU;
	User* prevU;
}*uOrigin, *uAux, uLogged;

struct Person {
	int idPerson;
	string apPerson;
	string amPerson;
	string namePerson;
	char CURP[19];
	string RFC;
	string fechaNaci;
	string calle;
	string colonia;
	string estado;
	string estadoCivil;
	string telefono;
	string ciudad;
	char identificacion[MAX_PATH];
	string sexo;
	string grupoOcup;
	string perfilRies;
	string identiString;
	Person* nextP;
	Person* prevP;
}*pOrigin, *pAux, pLogged;

struct Vaccine {
	int idVaccine;
	string tipo;
	string marca;
	string dosis;
	string claveVaccine;
	char description[MAX_PATH];
	float precio;
	Vaccine* nextV;
	Vaccine* prevV;
}*vOrigin, *vAux;

struct Carnet {
	int idCarnet;
	char curpCarnet[19];
	string vacunaCarnet;
	string dosisCarnet;
	string fechaDosisCarnet;
	string fechaDosisCarnet2;
	string loteMarca;
	string centroDeVacu;

	string apPersonCar;
	string amPersonCar;
	string namePersonCar;
	string RFCCar;
	string fechaNaciCar;
	string calleCar;
	string coloniaCar;
	string estadoCar;
	string estadoCivilCar;
	string telefonoCar;
	string ciudadCar;
	char identificacionCar[MAX_PATH];
	string sexoCar;
	string grupoOcupCar;
	string perfilRiesCar;
	string identiStringCar;

	string claveVaccineCar;
	char descriptionCar[MAX_PATH];
	float precioCar;

	Carnet* nextC;
	Carnet* prevC;
}*cOrigin, *cAux;
#pragma endregion

#pragma region CALLBACKS
BOOL CALLBACK fLogin(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK fRegisterUser(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK fPrincipal(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK fRegisterPerson(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK fDeletePerson(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK fChangePerson(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK fRegisterVaccine(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK fDeleteVaccine(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK fChangeVaccine(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK fRegisterCarnet(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK fDeleteCarnet(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK fChangeCarnet(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK fReportHeapSort(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK fReportQuickSort(HWND, UINT, WPARAM, LPARAM);
#pragma endregion 

#pragma region VARIABLES
HINSTANCE hGlobalInst;
HWND cbComboCivil;
HWND cbComboSexo;
HWND cbComboPerfil;
HWND cbComboIndetiti;
bool exitWindow = false;
string EMPTY_VALUE = "-1";
int globalId = 1;
int globalIdPerson = 1;
int globalIdVaccine = 1;
int globalIdCarnet = 1;
int globalIdHeapSort = 1;
int globalIdQuickSort = 1;
int idVaccineFounded;
int idPersonFounded;
fstream fileManager;
char estadoCivilchar[MAX_PATH];
char sexoChar[MAX_PATH];
char perfilChar[MAX_PATH];
char identitiChar[MAX_PATH];
string pImageTempPerson;
Vaccine* foundedVaccine;
Person* foundedPersona;
time_t actualTime;
tm* tiempo;
bool check1 = false, check2 = false;
string dosisGlobal;
Carnet* carnetFounded;
#pragma endregion 

#pragma region FUNCIONES
string getHwndText(HWND, int);
bool saveUser(string, string, string , string, string, int);
void clearHwnd(HWND, int);
bool findUser(string);
bool findUser(string, string);
void saveToFileUser();
void loadToFileUser();
void getMaxIdUser();
void saveMaxIdUser();
void clearUser();
bool savePerson(string, string, string, string, string, string, string, string, string, string, string, string, string, string,string,string, int);
bool searchPersonCopy(string);
bool searchPersonCopy2(string);
void saveToFilePerson();
void saveMaxIdPerson();
void clearPerson();
void getMaxIdPerson();
void loadToFilePerson();
void clearVaccine();
void saveMaxIdVaccine();
void getMaxIdVaccine();
void saveToFileVaccine();
bool saveVaccine(string, string, string, string, string, float, int);
bool searchVaccineCopy(string);
void loadToFileVaccine();
bool imprVaccine(HWND, int);
Vaccine* searchVacineLB(string);
void showVariablesVaccineDelete(HWND);
Vaccine* searchVaccine(string, Vaccine*);
void borrarVaccine();
bool imprPerson(HWND, int);
void showVariablesVaccineChange(HWND);
Vaccine* searchVaccineWithId(int, Vaccine*, string);
Vaccine* changeVaccine(Vaccine*, string, string, string, string, string, float);
bool searchVaccineCopy2(string, Vaccine*);
void showVariablesPersonDelete(HWND);
Person* searchPersonLB(string);
Person* searchPerson(string, Person*);
void borrarPerson();
void showVariablesPersonChange(HWND);
Person* searchPersonWithId(int, Person*);
bool searchPersonCopy2(string, string, Person*);
Person* changePerson(Person* , string , string , string , string , string , string , string , string , string , string , string , string , string , string, string, string);
bool findCarnet(string);
void saveToFileCarnet();
void getMaxIdCarnet();
void saveMaxIdCarnet();
void clearCarnet();
bool saveCarnet(string, string ,string, string , string , string , string , string , string , string , string , string , string , string , string , string , string , string , string , string , string , string , string , string , float , int );
void loadToFileCarnet();
void showVariablesCarnetCurpRe(HWND);
void showVariablesCarnetClaveRe(HWND);
void fechaDosisVacuna(HWND, int, int);
int day_month(int, int);
bool bisiesto(int);
void habilitarBoton(bool, bool, HWND);
void borrarCarnet();
Carnet* busquedaBinaria(Carnet*, int);
Carnet* findMid(Carnet*, Carnet*);
void showVariablesCarnetDelete(HWND );
void showVariablesCarnetChange(HWND );
void showVariablesCarnetCurpChange(HWND );
void showVariablesCarnetClaveChange(HWND );
Carnet* changeCarnet(Carnet*, string, string, string, string, string, string, string, string, string, string, string, string, string, string, string, string, string, string, string, string, string, string, string, string, float);
void llenarReporteQuickSort(HWND, int);
void llenarReporteHeapSort(HWND, int);
string juntarTextoQuickSort(Carnet*);
string juntarTextoHeapSort(Carnet*);
void saveMaxIdHeapSort();
void saveMaxIdQuickSort();
void getMaxIdHeapSort();
void getMaxIdQuickSort();
//void heapify(Carnet*, int);
//void intercambiar(Carnet*, Carnet*);
//Carnet* recorreListaXVeces(int, Carnet*);
//void heapSort(Carnet*, int);
//int countElementsList(Carnet*);
void reportHeapSort(int, int*, HWND, int);
void heapify(int* , int );
void heapSort(int* , int );
void reportQuickSort(int , string* , HWND , int );
void Quicksort(string* , int , int );
int Partition(string* , int , int );
void reportHeapSortTxt(int);
void reportQuickSortTxt(int);
#pragma endregion 

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, PSTR cmdLine, int cShow ) {
	hGlobalInst = hInst;
	uOrigin = uAux = NULL;
	getMaxIdUser();
	getMaxIdPerson();
	getMaxIdVaccine();
	getMaxIdCarnet();
	getMaxIdHeapSort();
	getMaxIdQuickSort();
	loadToFileUser();
	loadToFilePerson();
	loadToFileVaccine();
	loadToFileCarnet();
	HWND hLogin = CreateDialog(hInst,MAKEINTRESOURCE(DLG_LOGIN_USER) , NULL, fLogin);
	ShowWindow(hLogin, cShow);
	SetTimer(hLogin, TIMER_GENERICO, 1000, (TIMERPROC)NULL);
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));
	while (GetMessage(&msg, NULL, NULL, NULL)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

#pragma region CALLBACKS

BOOL CALLBACK fLogin(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
	switch (msg) {
	case WM_COMMAND: {
		if (LOWORD(wparam) == BTN_RETURN_LOGIN && HIWORD(wparam) == BN_CLICKED) {
			HWND hRegisterUser = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_REGISTER_USER), NULL, fRegisterUser);
			ShowWindow(hRegisterUser, SW_SHOW);
			DestroyWindow(hwnd);
		}
		else if (LOWORD(wparam) == BTN_OK_LOGIN && HIWORD(wparam) == BN_CLICKED) {
			string clav = getHwndText(hwnd, TXT_CLAVE_LOGIN);
			string password = getHwndText(hwnd, TXT_CONTRA_LOGIN);
			if (clav.compare("-1") == 0 || password.compare("-1") == 0) {
				MessageBox(NULL, "Campos incompletos", "Error", MB_ICONERROR);
				break;
			}
			if (uOrigin == NULL) {
				MessageBox(NULL, "No hay usuarios registrados", "Error", MB_ICONERROR);
				break;
			}
			if (findUser(clav, password)) {
				HWND hPrincipal = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_PRINCIPAL), NULL, fPrincipal);
				ShowWindow(hPrincipal, SW_SHOW);
				DestroyWindow(hwnd);
			}
			else {
				MessageBox(NULL, "Credenciales erroneas", "Error", MB_ICONERROR);
				break;
			}
		}
	}break;
	case WM_CLOSE:
		exitWindow = true;
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		if (exitWindow == true) {
			KillTimer(hwnd, TIMER_GENERICO);
			clearUser();
			clearPerson();
			clearVaccine();
			clearCarnet();
			PostQuitMessage(1);
		}
		break;
	}
	return FALSE;
}

BOOL CALLBACK fPrincipal(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
	switch (msg) {
	 case WM_INITDIALOG: {
		 HWND hLabelText = GetDlgItem(hwnd, ST_USER_PRIN);
		 SetWindowText(hLabelText, uLogged.nameUser.c_str());
	 }break;
	 case WM_COMMAND: {
		 if (LOWORD(wparam) == MENU_PERSONAS_REGISTRO && HIWORD(wparam) == BN_CLICKED) {
			 HWND hRegisterPerson = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_REG_PERSON), NULL, fRegisterPerson);
			 ShowWindow(hRegisterPerson, SW_SHOW);
			 DestroyWindow(hwnd);
		 }
		 else if (LOWORD(wparam) == MENU_VACUNAS_REGISTRO && HIWORD(wparam) == BN_CLICKED) {
			 HWND hRegistroVaccine = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_RE_VACUNA), NULL, fRegisterVaccine);
			 ShowWindow(hRegistroVaccine, SW_SHOW);
			 DestroyWindow(hwnd);
		 }
		 else if (LOWORD(wparam) == MENU_VACUNAS_BAJA && HIWORD(wparam) == BN_CLICKED) {
			 HWND hDeleteVaccine = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_DELETE_VACUNA), NULL, fDeleteVaccine);
			 ShowWindow(hDeleteVaccine, SW_SHOW);
			 DestroyWindow(hwnd);
		 }
		 else if (LOWORD(wparam) == MENU_VACUNAS_CAMBIO && HIWORD(wparam) == BN_CLICKED) {
			 HWND hChangeVaccine = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_CHANGE_VACCINE), NULL, fChangeVaccine);
			 ShowWindow(hChangeVaccine, SW_SHOW);
			 DestroyWindow(hwnd);
		 }
		 else if (LOWORD(wparam) == MENU_PERSONAS_BAJA && HIWORD(wparam) == BN_CLICKED) {
			 HWND hDeletePersonas = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_BAJA_PERSONAS), NULL, fDeletePerson);
			 ShowWindow(hDeletePersonas, SW_SHOW);
			 DestroyWindow(hwnd);
		 }
		 else if (LOWORD(wparam) == MENU_PERSONAS_CAMBIO && HIWORD(wparam) == BN_CLICKED) {
			 HWND hChangePersonas = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_CHANGE_PERSON), NULL, fChangePerson);
			 ShowWindow(hChangePersonas, SW_SHOW);
			 DestroyWindow(hwnd);
		 }
		 else if (LOWORD(wparam) == MENU_CARNE_RE && HIWORD(wparam) == BN_CLICKED) {
			 HWND hRegisterCarnet = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_REG_CARNET), NULL, fRegisterCarnet);
			 ShowWindow(hRegisterCarnet, SW_SHOW);
			 DestroyWindow(hwnd);
		 }
		 else if (LOWORD(wparam) == MENU_CARNE_BAJA && HIWORD(wparam) == BN_CLICKED) {
			 HWND hDeleteCarnet = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_DELETE_CARNET), NULL, fDeleteCarnet);
			 ShowWindow(hDeleteCarnet, SW_SHOW);
			 DestroyWindow(hwnd);
		 }
		 else if (LOWORD(wparam) == MENU_CARNE_CAMBIO && HIWORD(wparam) == BN_CLICKED) {
			 HWND hChangeCarnet = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_CHANGE_CARNET), NULL, fChangeCarnet);
			 ShowWindow(hChangeCarnet, SW_SHOW);
			 DestroyWindow(hwnd);
		 }
		 else if (LOWORD(wparam) == BTN_MENU_REPORT_NAME && HIWORD(wparam) == BN_CLICKED) {
			 HWND hQuickSort = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_REPORTE_QUICKSORT), NULL, fReportQuickSort);
			 ShowWindow(hQuickSort, SW_SHOW);
			 DestroyWindow(hwnd);
		 }
		 else if (LOWORD(wparam) == BTN_MENU_REPORT_ID && HIWORD(wparam) == BN_CLICKED) {
			 HWND hHeapSort = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_REPORTE_HEAPSORT), NULL, fReportHeapSort);
			 ShowWindow(hHeapSort, SW_SHOW);
			 DestroyWindow(hwnd);
		 }
	 }break;
	 case WM_CLOSE: {
		HWND hLogin = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_LOGIN_USER), NULL, fLogin);
		ShowWindow(hLogin, SW_SHOW);
		DestroyWindow(hwnd);
	 }
	  break;
	 case WM_DESTROY:
		break;
	}
	return FALSE;
}

BOOL CALLBACK fRegisterUser(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
	switch (msg) {
	case WM_COMMAND: {
		if (LOWORD(wparam) == BTN_RETURN_REGISTER && HIWORD(wparam) == BN_CLICKED) {
			HWND hLogin = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_LOGIN_USER), NULL, fLogin);
			ShowWindow(hLogin, SW_SHOW);
			DestroyWindow(hwnd);
		}
		else if (LOWORD(wparam) == BTN_OK_REGISTER && HIWORD(wparam) == BN_CLICKED) {
			string username = getHwndText(hwnd, TXT_NAME_RE);
			string password = getHwndText(hwnd, TXT_CONTRA_RE);
			string amU = getHwndText(hwnd, TXT_AM_RE);
			string apU = getHwndText(hwnd, TXT_AP_RE);
			string clav = getHwndText(hwnd, TXT_CLAVE_RE);
			wstring clavWstring = wstring(clav.begin(), clav.end());
			const wchar_t* checarClav;
			checarClav = clavWstring.c_str();
			if (wcschr(checarClav, ' ') != nullptr) {
				MessageBox(NULL, "La clave tiene espacios en blanco", "Error", MB_ICONERROR);
				break;
			}
			if (clav.compare("-1") == 0 || password.compare("-1") == 0 || username.compare("-1") == 0 || amU.compare("-1")==0 || apU.compare("-1")== 0) {
				MessageBox(NULL, "Campos incompletos", "Error", MB_ICONERROR);
				break;
			}
			if (saveUser(username, password,amU,apU, clav, globalId++) == false) {
				--globalId;
				MessageBox(NULL, "Clave de Usuario repetido", "Error", MB_ICONERROR);
			}
			else {
				saveMaxIdUser();
				saveToFileUser();
				MessageBox(NULL, "Usuario registrado con exito", "EXITO", MB_ICONINFORMATION);
			}
			clearHwnd(hwnd, TXT_NAME_RE);
			clearHwnd(hwnd, TXT_CONTRA_RE);
			clearHwnd(hwnd, TXT_AM_RE);
			clearHwnd(hwnd, TXT_AP_RE);
			clearHwnd(hwnd, TXT_CLAVE_RE);
		}
	}break;
	case WM_CLOSE: {
		HWND hLogin = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_LOGIN_USER), NULL, fLogin);
		ShowWindow(hLogin, SW_SHOW);
		DestroyWindow(hwnd);
	}
		break;
	case WM_DESTROY:
		
		break;
	}
	return FALSE;
}

BOOL CALLBACK fRegisterPerson(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
	switch (msg) {
	case WM_INITDIALOG: {
		cbComboCivil = GetDlgItem(hwnd, CB_CIVIL_RE_PERSON);
		cbComboSexo = GetDlgItem(hwnd, CB_SEXO_RE_PERSON);
		cbComboPerfil = GetDlgItem(hwnd, CB_PERFIL_RE_PERSON);
		cbComboIndetiti = GetDlgItem(hwnd, CB_IDENTIDAD_RE_PERSON);
		SendMessage(cbComboCivil, CB_ADDSTRING, NULL, (LPARAM)"Escoga una opcion...");
		SendMessage(cbComboCivil, CB_ADDSTRING, NULL, (LPARAM)"Soltero(a)");
		SendMessage(cbComboCivil, CB_ADDSTRING, NULL, (LPARAM)"Casado(a)");
		SendMessage(cbComboCivil, CB_ADDSTRING, NULL, (LPARAM)"Divorciado(a)");
		SendMessage(cbComboCivil, CB_ADDSTRING, NULL, (LPARAM)"Viudo(a)");
		SendMessage(cbComboSexo, CB_ADDSTRING, NULL, (LPARAM)"Escoga una opcion...");
		SendMessage(cbComboSexo, CB_ADDSTRING, NULL, (LPARAM)"Masculino");
		SendMessage(cbComboSexo, CB_ADDSTRING, NULL, (LPARAM)"Femenino");
		SendMessage(cbComboSexo, CB_ADDSTRING, NULL, (LPARAM)"Otro");
		SendMessage(cbComboPerfil, CB_ADDSTRING, NULL, (LPARAM)"Escoga una opcion...");
		SendMessage(cbComboPerfil, CB_ADDSTRING, NULL, (LPARAM)"Ninguno");
		SendMessage(cbComboPerfil, CB_ADDSTRING, NULL, (LPARAM)"PersonaMayor");
		SendMessage(cbComboPerfil, CB_ADDSTRING, NULL, (LPARAM)"Embarazada");
		SendMessage(cbComboPerfil, CB_ADDSTRING, NULL, (LPARAM)"Enfermedad");
		SendMessage(cbComboIndetiti, CB_ADDSTRING, NULL, (LPARAM)"Escoga una opcion...");
		SendMessage(cbComboIndetiti, CB_ADDSTRING, NULL, (LPARAM)"INE");
		SendMessage(cbComboIndetiti, CB_ADDSTRING, NULL, (LPARAM)"ACTA");
		SendMessage(cbComboIndetiti, CB_ADDSTRING, NULL, (LPARAM)"Otro");

		SendMessage(cbComboCivil, CB_SETCURSEL, 0, NULL);
		SendMessage(cbComboSexo, CB_SETCURSEL, 0, NULL);
		SendMessage(cbComboPerfil, CB_SETCURSEL, 0, NULL);
		SendMessage(cbComboIndetiti, CB_SETCURSEL, 0, NULL);
	}break;
	case WM_COMMAND: {
		if (LOWORD(wparam) == MENU_PANTALLAPRINCIPAL && HIWORD(wparam) == BN_CLICKED) {
			HWND hPrincipal = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_PRINCIPAL), NULL, fPrincipal);
			ShowWindow(hPrincipal, SW_SHOW);
			DestroyWindow(hwnd);
		}
		else if (LOWORD(wparam) == BTN_OK_RE_PERSON && HIWORD(wparam) == BN_CLICKED) {
			string apPerson = getHwndText(hwnd, TXT_AP_RE_PERSON);
			string amPerson = getHwndText(hwnd, TXT_AM_RE_PERSON);
			string namePerson = getHwndText(hwnd, TXT_NAME_RE_PERSON);
			string tempCurp = getHwndText(hwnd, TXT_CURP_RE_PERSON);
			string RFC = getHwndText(hwnd, TXT_RFC_RE_PERSON);
			string calle = getHwndText(hwnd, TXT_CALLE_RE_PERSON);
			string colonia = getHwndText(hwnd, TXT_COLONIA_RE_PERSON);
			string estado = getHwndText(hwnd, TXT_ESTADO_RE_PERSON);
			string telefono = getHwndText(hwnd, TXT_TELEFO_RE_PERSON);
			string grupo = getHwndText(hwnd, TXT_GRUPO_RE_PERSON);
			string ciudad = getHwndText(hwnd, TXT_CIUDAD_RE_PERSON);
			HWND fecha = GetDlgItem(hwnd, DTP_FECHA_RE_PERSON);
			int iFecLength = GetWindowTextLength(fecha) + 1;
			char cFecha[15];
			GetWindowText(fecha, cFecha, iFecLength);
			string fechaDTP(cFecha);

			int index = SendMessage(cbComboCivil, CB_GETCURSEL, NULL, NULL);
			int index2 = SendMessage(cbComboSexo, CB_GETCURSEL, NULL, NULL);
			int index3 = SendMessage(cbComboPerfil, CB_GETCURSEL, NULL, NULL);
			int index4 = SendMessage(cbComboIndetiti, CB_GETCURSEL, NULL, NULL);

			if (index < 1) {
				MessageBox(NULL, "No selecciono el estado civil", "Error", MB_ICONERROR);
				break;
			}
			else {
				int length = GetWindowTextLength(cbComboCivil);
				GetWindowText(cbComboCivil, estadoCivilchar, length + 1);
			}
			if (index2 < 1) {
				MessageBox(NULL, "No selecciono el sexo", "Error", MB_ICONERROR);
				break;
			}
			else {
				int length = GetWindowTextLength(cbComboSexo);
				GetWindowText(cbComboSexo, sexoChar, length + 1);
			}
			if (index3 < 1) {
				MessageBox(NULL, "No selecciono el perfil de riesgo", "Error", MB_ICONERROR);
				break;
			}
			else {
				int length = GetWindowTextLength(cbComboPerfil);
				GetWindowText(cbComboPerfil, perfilChar, length + 1);
			}
			if (index4 < 1) {
				MessageBox(NULL, "No selecciono el documento de identidad", "Error", MB_ICONERROR);
				break;
			}
			else {
				int length = GetWindowTextLength(cbComboIndetiti);
				GetWindowText(cbComboIndetiti, identitiChar, length + 1);
			}
			string civil = estadoCivilchar;
			string sexo = sexoChar;
			string perfil = perfilChar;
			string identiti = identitiChar;
			wstring curpWstring = wstring(tempCurp.begin(), tempCurp.end());
			wstring rfcWstring = wstring(RFC.begin(), RFC.end());
			const wchar_t* checarCurp;
			const wchar_t* checarRFC;
			checarCurp = curpWstring.c_str();
			checarRFC = rfcWstring.c_str();
			if (wcschr(checarCurp, ' ') != nullptr) {
				MessageBox(NULL, "El CURP tiene espacios en blanco", "Error", MB_ICONERROR);
				break;
			}
			if (wcschr(checarRFC, ' ') != nullptr) {
				MessageBox(NULL, "El RFC tiene espacios en blanco", "Error", MB_ICONERROR);
				break;
			}
			if (apPerson.compare("-1") == 0 || amPerson.compare("-1") == 0 || namePerson.compare("-1") == 0 || tempCurp.compare("-1") == 0 || RFC.compare("-1") == 0 || calle.compare("-1") == 0 || colonia.compare("-1") == 0 || estado.compare("-1") == 0 || telefono.compare("-1") == 0 || grupo.compare("-1") == 0 || ciudad.compare("-1") == 0) {
				MessageBox(NULL, "Campos incompletos", "Error", MB_ICONERROR);
				break;
			}
			if (savePerson(apPerson, amPerson, namePerson, tempCurp, RFC, fechaDTP, calle, colonia, estado, civil, telefono, sexo, grupo, perfil, ciudad, identiti, globalIdPerson++) == false) {
				--globalIdPerson;
				MessageBox(NULL, "CURP o RFC repetido", "Error", MB_ICONERROR);
			}
			else {
				saveMaxIdPerson();
				saveToFilePerson();
				MessageBox(NULL, "Persona registrado con exito", "EXITO", MB_ICONINFORMATION);
			}
			clearHwnd(hwnd, TXT_AP_RE_PERSON);
			clearHwnd(hwnd, TXT_AM_RE_PERSON);
			clearHwnd(hwnd, TXT_NAME_RE_PERSON);
			clearHwnd(hwnd, TXT_CURP_RE_PERSON);
			clearHwnd(hwnd, TXT_RFC_RE_PERSON);
			clearHwnd(hwnd, TXT_CALLE_RE_PERSON);
			clearHwnd(hwnd, TXT_COLONIA_RE_PERSON);
			clearHwnd(hwnd, TXT_ESTADO_RE_PERSON);
			clearHwnd(hwnd, TXT_TELEFO_RE_PERSON);
			clearHwnd(hwnd, TXT_GRUPO_RE_PERSON);
			clearHwnd(hwnd, TXT_CIUDAD_RE_PERSON);
			HWND hPBImagen = GetDlgItem(hwnd, BM_IMAGE_RE_PERSON);
			SendMessage(hPBImagen, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)NULL);
		}
		else if (LOWORD(wparam) == BTN_CARG_RE_PERSON && HIWORD(wparam) == BN_CLICKED) {
		
			OPENFILENAME ofn;
			ZeroMemory(&ofn, sizeof(OPENFILENAME));
			char cDirFile[MAX_PATH] = "";
			ofn.hwndOwner = hwnd;
			ofn.lpstrFile = cDirFile;
			ofn.lStructSize = sizeof(OPENFILENAME);
			ofn.nMaxFile = MAX_PATH;
			ofn.lpstrDefExt = "txt";
			ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_NOCHANGEDIR;
			ofn.lpstrFilter = "Todos los archivos\0*.*\0";

			if (GetOpenFileName(&ofn)) {

				HWND hPBImagen = GetDlgItem(hwnd, BM_IMAGE_RE_PERSON);
				HBITMAP hImagePerson = (HBITMAP)LoadImage(NULL, cDirFile, IMAGE_BITMAP, 100, 100, LR_LOADFROMFILE);
				SendMessage(hPBImagen, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hImagePerson);
				pImageTempPerson = cDirFile;
			}
		}
		else if (LOWORD(wparam) == MENU_VACUNAS_REGISTRO && HIWORD(wparam) == BN_CLICKED) {
			HWND hRegistroVaccine = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_RE_VACUNA), NULL, fRegisterVaccine);
			ShowWindow(hRegistroVaccine, SW_SHOW);
			DestroyWindow(hwnd);
		}
		else if (LOWORD(wparam) == MENU_VACUNAS_BAJA && HIWORD(wparam) == BN_CLICKED) {
			HWND hDeleteVaccine = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_DELETE_VACUNA), NULL, fDeleteVaccine);
			ShowWindow(hDeleteVaccine, SW_SHOW);
			DestroyWindow(hwnd);
		}
		else if (LOWORD(wparam) == MENU_VACUNAS_CAMBIO && HIWORD(wparam) == BN_CLICKED) {
			HWND hChangeVaccine = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_CHANGE_VACCINE), NULL, fChangeVaccine);
			ShowWindow(hChangeVaccine, SW_SHOW);
			DestroyWindow(hwnd);
		}
		else if (LOWORD(wparam) == MENU_PERSONAS_BAJA && HIWORD(wparam) == BN_CLICKED) {
			HWND hDeletePersonas = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_BAJA_PERSONAS), NULL, fDeletePerson);
			ShowWindow(hDeletePersonas, SW_SHOW);
			DestroyWindow(hwnd);
		}
		else if (LOWORD(wparam) == MENU_PERSONAS_CAMBIO && HIWORD(wparam) == BN_CLICKED) {
			HWND hChangePersonas = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_CHANGE_PERSON), NULL, fChangePerson);
			ShowWindow(hChangePersonas, SW_SHOW);
			DestroyWindow(hwnd);
		}
		else if (LOWORD(wparam) == MENU_CARNE_RE && HIWORD(wparam) == BN_CLICKED) {
			HWND hRegisterCarnet = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_REG_CARNET), NULL, fRegisterCarnet);
			ShowWindow(hRegisterCarnet, SW_SHOW);
			DestroyWindow(hwnd);
		}
		else if (LOWORD(wparam) == MENU_CARNE_BAJA && HIWORD(wparam) == BN_CLICKED) {
		HWND hDeleteCarnet = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_DELETE_CARNET), NULL, fDeleteCarnet);
		ShowWindow(hDeleteCarnet, SW_SHOW);
		DestroyWindow(hwnd);
		 }
		else if (LOWORD(wparam) == MENU_CARNE_CAMBIO && HIWORD(wparam) == BN_CLICKED) {
		HWND hChangeCarnet = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_CHANGE_CARNET), NULL, fChangeCarnet);
		ShowWindow(hChangeCarnet, SW_SHOW);
		DestroyWindow(hwnd);
		 }
		else if (LOWORD(wparam) == BTN_MENU_REPORT_NAME && HIWORD(wparam) == BN_CLICKED) {
		HWND hQuickSort = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_REPORTE_QUICKSORT), NULL, fReportQuickSort);
		ShowWindow(hQuickSort, SW_SHOW);
		DestroyWindow(hwnd);
		 }
		else if (LOWORD(wparam) == BTN_MENU_REPORT_ID && HIWORD(wparam) == BN_CLICKED) {
		HWND hHeapSort = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_REPORTE_HEAPSORT), NULL, fReportHeapSort);
		ShowWindow(hHeapSort, SW_SHOW);
		DestroyWindow(hwnd);
		 }

	}break;
	case WM_CLOSE: {
		HWND hLogin = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_LOGIN_USER), NULL, fLogin);
		ShowWindow(hLogin, SW_SHOW);
		DestroyWindow(hwnd);
	}break;
	case WM_DESTROY:
		break;
	}
	return FALSE;
}

BOOL CALLBACK fRegisterVaccine(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
	switch (msg) {
	case WM_INITDIALOG: {

	}break;
	case WM_COMMAND: {
		if (LOWORD(wparam) == MENU_PERSONAS_REGISTRO && HIWORD(wparam) == BN_CLICKED) {
			HWND hRegisterPerson = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_REG_PERSON), NULL, fRegisterPerson);
			ShowWindow(hRegisterPerson, SW_SHOW);
			DestroyWindow(hwnd);
		}
		else if (LOWORD(wparam) == MENU_PANTALLAPRINCIPAL && HIWORD(wparam) == BN_CLICKED) {
			HWND hPrincipal = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_PRINCIPAL), NULL, fPrincipal);
			ShowWindow(hPrincipal, SW_SHOW);
			DestroyWindow(hwnd);
		}
		else if (LOWORD(wparam) == MENU_VACUNAS_BAJA && HIWORD(wparam) == BN_CLICKED) {
			HWND hDeleteVaccine = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_DELETE_VACUNA), NULL, fDeleteVaccine);
			ShowWindow(hDeleteVaccine, SW_SHOW);
			DestroyWindow(hwnd);
		}
		else if (LOWORD(wparam) == MENU_VACUNAS_CAMBIO && HIWORD(wparam) == BN_CLICKED) {
			HWND hChangeVaccine = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_CHANGE_VACCINE), NULL, fChangeVaccine);
			ShowWindow(hChangeVaccine, SW_SHOW);
			DestroyWindow(hwnd);
		}
		else if (LOWORD(wparam) == MENU_PERSONAS_BAJA && HIWORD(wparam) == BN_CLICKED) {
			HWND hDeletePersonas = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_BAJA_PERSONAS), NULL, fDeletePerson);
			ShowWindow(hDeletePersonas, SW_SHOW);
			DestroyWindow(hwnd);
		}
		else if (LOWORD(wparam) == MENU_PERSONAS_CAMBIO && HIWORD(wparam) == BN_CLICKED) {
			HWND hChangePersonas = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_CHANGE_PERSON), NULL, fChangePerson);
			ShowWindow(hChangePersonas, SW_SHOW);
			DestroyWindow(hwnd);
		}
		else if (LOWORD(wparam) == MENU_CARNE_RE && HIWORD(wparam) == BN_CLICKED) {
			HWND hRegisterCarnet = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_REG_CARNET), NULL, fRegisterCarnet);
			ShowWindow(hRegisterCarnet, SW_SHOW);
			DestroyWindow(hwnd);
		}
		else if (LOWORD(wparam) == MENU_CARNE_BAJA && HIWORD(wparam) == BN_CLICKED) {
			HWND hDeleteCarnet = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_DELETE_CARNET), NULL, fDeleteCarnet);
			ShowWindow(hDeleteCarnet, SW_SHOW);
			DestroyWindow(hwnd);
		}
		else if (LOWORD(wparam) == MENU_CARNE_CAMBIO && HIWORD(wparam) == BN_CLICKED) {
			HWND hChangeCarnet = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_CHANGE_CARNET), NULL, fChangeCarnet);
			ShowWindow(hChangeCarnet, SW_SHOW);
			DestroyWindow(hwnd);
		}
		else if (LOWORD(wparam) == BTN_MENU_REPORT_NAME && HIWORD(wparam) == BN_CLICKED) {
			HWND hQuickSort = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_REPORTE_QUICKSORT), NULL, fReportQuickSort);
			ShowWindow(hQuickSort, SW_SHOW);
			DestroyWindow(hwnd);
		}
		else if (LOWORD(wparam) == BTN_MENU_REPORT_ID && HIWORD(wparam) == BN_CLICKED) {
			HWND hHeapSort = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_REPORTE_HEAPSORT), NULL, fReportHeapSort);
			ShowWindow(hHeapSort, SW_SHOW);
			DestroyWindow(hwnd);
		}
		else if (LOWORD(wparam) == BTN_OK_RE_VACUNA && HIWORD(wparam) == BN_CLICKED) {
			string tipo = getHwndText(hwnd, TXT_TIPO_VACUNA);
			string marca = getHwndText(hwnd, TXT_MARCA_VACUNA);
			string dosis = getHwndText(hwnd, TXT_DOSIS_VACUNA);
			string clave = getHwndText(hwnd, TXT_CLAVE_VACUNA);
			string descripcion = getHwndText(hwnd, TXT_DES_VACUNA);
			string precio = getHwndText(hwnd, TXT_PRECIO_VACUNA);

			char cDes[50];
			float fPrice = atof(precio.c_str());
			float fDosis = atof(dosis.c_str());
			strcpy_s(cDes, descripcion.c_str());
			if (clave.compare("-1") == 0 || descripcion.compare("-1") == 0 || precio.compare("-1") == 0 || tipo.compare("-1") == 0 || marca.compare("-1") == 0 || dosis.compare("-1") == 0) {
				MessageBox(NULL, "Campos incompletos", "Error", MB_ICONERROR);
				break;
			}
			if (fPrice <= 0) {
				MessageBox(NULL, "La vacuna tiene que tener un valor mayor a 0", "Error", MB_ICONERROR);
				break;
			}
			if (fDosis > 2 || fDosis < 1) {
				MessageBox(NULL, "La dosis de las vacunas solo pueden ser 1 o 2", "Error", MB_ICONERROR);
				break;
			}
			if (saveVaccine(tipo, marca, dosis, clave, descripcion, fPrice, globalIdVaccine++) == false) {
				--globalIdVaccine;
				MessageBox(NULL, "Clave de vacuna repetida", "Error", MB_ICONERROR);
			}
			else {
				saveMaxIdVaccine();
				saveToFileVaccine();
				MessageBox(NULL, "Vacuna registrado con exito", "EXITO", MB_ICONINFORMATION);
			}
			clearHwnd(hwnd, TXT_TIPO_VACUNA);
			clearHwnd(hwnd, TXT_MARCA_VACUNA);
			clearHwnd(hwnd, TXT_DOSIS_VACUNA);
			clearHwnd(hwnd, TXT_CLAVE_VACUNA);
			clearHwnd(hwnd, TXT_DES_VACUNA);
			clearHwnd(hwnd, TXT_PRECIO_VACUNA);
		}
	}break;
	case WM_CLOSE: {
		HWND hLogin = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_LOGIN_USER), NULL, fLogin);
		ShowWindow(hLogin, SW_SHOW);
		DestroyWindow(hwnd);
	}
	break;
	case WM_DESTROY:
		break;
	}
	return FALSE;
}

BOOL CALLBACK fDeleteVaccine(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
	switch (msg) {
	case WM_INITDIALOG: {
		imprVaccine(hwnd, LB_VACUNA_DELETE);
		HWND btnOk = GetDlgItem(hwnd, BTN_OK_VACUNADELETE);
		EnableWindow(btnOk, false);
	}break;
	case WM_COMMAND: {
		if (LOWORD(wparam) == MENU_PERSONAS_REGISTRO && HIWORD(wparam) == BN_CLICKED) {
			HWND hRegisterPerson = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_REG_PERSON), NULL, fRegisterPerson);
			ShowWindow(hRegisterPerson, SW_SHOW);
			DestroyWindow(hwnd);
		}
		else if (LOWORD(wparam) == MENU_VACUNAS_REGISTRO && HIWORD(wparam) == BN_CLICKED) {
			HWND hRegistroVaccine = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_RE_VACUNA), NULL, fRegisterVaccine);
			ShowWindow(hRegistroVaccine, SW_SHOW);
			DestroyWindow(hwnd);
		}
		else if (LOWORD(wparam) == MENU_PANTALLAPRINCIPAL && HIWORD(wparam) == BN_CLICKED) {
			HWND hPrincipal = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_PRINCIPAL), NULL, fPrincipal);
			ShowWindow(hPrincipal, SW_SHOW);
			DestroyWindow(hwnd);
		}
		else if (LOWORD(wparam) == MENU_VACUNAS_CAMBIO && HIWORD(wparam) == BN_CLICKED) {
			HWND hChangeVaccine = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_CHANGE_VACCINE), NULL, fChangeVaccine);
			ShowWindow(hChangeVaccine, SW_SHOW);
			DestroyWindow(hwnd);
		}
		else if (LOWORD(wparam) == MENU_PERSONAS_BAJA && HIWORD(wparam) == BN_CLICKED) {
			HWND hDeletePersonas = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_BAJA_PERSONAS), NULL, fDeletePerson);
			ShowWindow(hDeletePersonas, SW_SHOW);
			DestroyWindow(hwnd);
		}
		else if (LOWORD(wparam) == MENU_PERSONAS_CAMBIO && HIWORD(wparam) == BN_CLICKED) {
			HWND hChangePersonas = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_CHANGE_PERSON), NULL, fChangePerson);
			ShowWindow(hChangePersonas, SW_SHOW);
			DestroyWindow(hwnd);
		}
		else if (LOWORD(wparam) == MENU_CARNE_RE && HIWORD(wparam) == BN_CLICKED) {
			HWND hRegisterCarnet = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_REG_CARNET), NULL, fRegisterCarnet);
			ShowWindow(hRegisterCarnet, SW_SHOW);
			DestroyWindow(hwnd);
		}
		else if (LOWORD(wparam) == MENU_CARNE_BAJA && HIWORD(wparam) == BN_CLICKED) {
			HWND hDeleteCarnet = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_DELETE_CARNET), NULL, fDeleteCarnet);
			ShowWindow(hDeleteCarnet, SW_SHOW);
			DestroyWindow(hwnd);
		}
		else if (LOWORD(wparam) == MENU_CARNE_CAMBIO && HIWORD(wparam) == BN_CLICKED) {
			HWND hChangeCarnet = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_CHANGE_CARNET), NULL, fChangeCarnet);
			ShowWindow(hChangeCarnet, SW_SHOW);
			DestroyWindow(hwnd);
		}
		else if (LOWORD(wparam) == BTN_MENU_REPORT_NAME && HIWORD(wparam) == BN_CLICKED) {
			HWND hQuickSort = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_REPORTE_QUICKSORT), NULL, fReportQuickSort);
			ShowWindow(hQuickSort, SW_SHOW);
			DestroyWindow(hwnd);
		}
		else if (LOWORD(wparam) == BTN_MENU_REPORT_ID && HIWORD(wparam) == BN_CLICKED) {
			HWND hHeapSort = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_REPORTE_HEAPSORT), NULL, fReportHeapSort);
			ShowWindow(hHeapSort, SW_SHOW);
			DestroyWindow(hwnd);
		}
		else if (HIWORD(wparam) == LBN_DBLCLK) {

			showVariablesVaccineDelete(hwnd);
			vAux = vOrigin;
			HWND btnOk = GetDlgItem(hwnd, BTN_OK_VACUNADELETE);
			EnableWindow(btnOk, true);
		}

		else if (LOWORD(wparam) == BTN_OK_VACUNADELETE && HIWORD(wparam) == BN_CLICKED) {
			string searchVacc = getHwndText(hwnd, TXT_CLAVE_VACUNADELETE);
			if (searchVacc.compare("-1") == 0) {
				MessageBox(NULL, "Seleccione la vacuna a eliminar", "Error", MB_ICONERROR);
				break;
			}
			foundedVaccine = vAux = searchVaccine(searchVacc, vAux);
			if (foundedVaccine == NULL) {
				MessageBox(NULL, "Vacuna no encontrada", "Error", MB_ICONERROR);
				vAux = vOrigin;
				break;
			}
			else {
				borrarVaccine();
				saveToFileVaccine();
				MessageBox(NULL, "Vacuna eliminada", "Yeih", MB_ICONINFORMATION);
			}
		}

	}break;
	case WM_CLOSE: {
		HWND hLogin = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_LOGIN_USER), NULL, fLogin);
		ShowWindow(hLogin, SW_SHOW);
		DestroyWindow(hwnd);
	}
	break;
	case WM_DESTROY:
		break;
	}
	return FALSE;
}

BOOL CALLBACK fChangeVaccine(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
	switch (msg) {
	case WM_INITDIALOG: {
		imprVaccine(hwnd, LB_VACUNA_CHANGE);
		HWND btnOk = GetDlgItem(hwnd, BTN_OK_VACUNACHANGE);
		EnableWindow(btnOk, false);
	}break;
	case WM_COMMAND: {
		if (LOWORD(wparam) == MENU_PERSONAS_REGISTRO && HIWORD(wparam) == BN_CLICKED) {
			HWND hRegisterPerson = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_REG_PERSON), NULL, fRegisterPerson);
			ShowWindow(hRegisterPerson, SW_SHOW);
			DestroyWindow(hwnd);
		}
		else if (LOWORD(wparam) == MENU_VACUNAS_REGISTRO && HIWORD(wparam) == BN_CLICKED) {
			HWND hRegistroVaccine = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_RE_VACUNA), NULL, fRegisterVaccine);
			ShowWindow(hRegistroVaccine, SW_SHOW);
			DestroyWindow(hwnd);
		}
		else if (LOWORD(wparam) == MENU_PANTALLAPRINCIPAL && HIWORD(wparam) == BN_CLICKED) {
			HWND hPrincipal = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_PRINCIPAL), NULL, fPrincipal);
			ShowWindow(hPrincipal, SW_SHOW);
			DestroyWindow(hwnd);
		}
		else if (LOWORD(wparam) == MENU_VACUNAS_BAJA && HIWORD(wparam) == BN_CLICKED) {
			HWND hDeleteVaccine = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_DELETE_VACUNA), NULL, fDeleteVaccine);
			ShowWindow(hDeleteVaccine, SW_SHOW);
			DestroyWindow(hwnd);
		}
		else if (LOWORD(wparam) == MENU_PERSONAS_BAJA && HIWORD(wparam) == BN_CLICKED) {
			HWND hDeletePersonas = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_BAJA_PERSONAS), NULL, fDeletePerson);
			ShowWindow(hDeletePersonas, SW_SHOW);
			DestroyWindow(hwnd);
		}
		else if (LOWORD(wparam) == MENU_PERSONAS_CAMBIO && HIWORD(wparam) == BN_CLICKED) {
			HWND hChangePersonas = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_CHANGE_PERSON), NULL, fChangePerson);
			ShowWindow(hChangePersonas, SW_SHOW);
			DestroyWindow(hwnd);
		}
		else if (LOWORD(wparam) == MENU_CARNE_RE && HIWORD(wparam) == BN_CLICKED) {
			HWND hRegisterCarnet = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_REG_CARNET), NULL, fRegisterCarnet);
			ShowWindow(hRegisterCarnet, SW_SHOW);
			DestroyWindow(hwnd);
		}
		else if (LOWORD(wparam) == MENU_CARNE_BAJA && HIWORD(wparam) == BN_CLICKED) {
			HWND hDeleteCarnet = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_DELETE_CARNET), NULL, fDeleteCarnet);
			ShowWindow(hDeleteCarnet, SW_SHOW);
			DestroyWindow(hwnd);
		}
		else if (LOWORD(wparam) == MENU_CARNE_CAMBIO && HIWORD(wparam) == BN_CLICKED) {
			HWND hChangeCarnet = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_CHANGE_CARNET), NULL, fChangeCarnet);
			ShowWindow(hChangeCarnet, SW_SHOW);
			DestroyWindow(hwnd);
		}
		else if (LOWORD(wparam) == BTN_MENU_REPORT_NAME && HIWORD(wparam) == BN_CLICKED) {
			HWND hQuickSort = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_REPORTE_QUICKSORT), NULL, fReportQuickSort);
			ShowWindow(hQuickSort, SW_SHOW);
			DestroyWindow(hwnd);
		}
		else if (LOWORD(wparam) == BTN_MENU_REPORT_ID && HIWORD(wparam) == BN_CLICKED) {
			HWND hHeapSort = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_REPORTE_HEAPSORT), NULL, fReportHeapSort);
			ShowWindow(hHeapSort, SW_SHOW);
			DestroyWindow(hwnd);
		}
		else if (HIWORD(wparam) == LBN_DBLCLK) {

			showVariablesVaccineChange(hwnd);
			vAux = vOrigin;
			HWND btnOk = GetDlgItem(hwnd, BTN_OK_VACUNACHANGE);
			EnableWindow(btnOk, true);
		}
		else if (LOWORD(wparam) == BTN_OK_VACUNACHANGE && HIWORD(wparam) == BN_CLICKED) {
			string claveT = getHwndText(hwnd, TXT_CLAVE_VACUNACHANGE);
			string tipoT = getHwndText(hwnd, TXT_TIPO_VACUNACHANGE);
			string marcaT = getHwndText(hwnd, TXT_MARCA_VACUNACHANGE);
			string dosisT = getHwndText(hwnd, TXT_DOSIS_VACUNACHANGE);
			string descT = getHwndText(hwnd, TXT_DES_VACUNACHANGE);
			string precioT = getHwndText(hwnd, TXT_PRECIO_VACUNACHANGE);
			float fDosis = atof(dosisT.c_str());
			float fPrice = atof(precioT.c_str());
			if (claveT.compare("-1") == 0 || tipoT.compare("-1") == 0 || marcaT.compare("-1") == 0 || dosisT.compare("-1") == 0 || descT.compare("-1") == 0 || precioT.compare("-1") == 0) {
				MessageBox(NULL, "LLene los espacios con la nueva informacion", "Error", MB_ICONERROR);
				break;
			}
			if (fPrice <= 0) {
				MessageBox(NULL, "La vacuna tiene que tener un valor mayor a 0", "Error", MB_ICONERROR);
				break;
			}
			if (fDosis > 2 || fDosis < 1) {
				MessageBox(NULL, "La dosis de las vacunas solo pueden ser 1 o 2", "Error", MB_ICONERROR);
				break;
			}
			foundedVaccine = vAux = searchVaccineWithId(idVaccineFounded, vAux, claveT);
			if (foundedVaccine == NULL) {
				MessageBox(NULL, "Vacuna no encontrada", "Error", MB_ICONERROR);
				vAux = vOrigin;
				break;
			}
			/*bool checkDouble = searchVaccineCopy2(claveT, vAux);
			if (checkDouble == true) {
				MessageBox(NULL, "Clave de vacuna repetida", "Error", MB_ICONERROR);
				vAux = vOrigin;
				break;
			}*/
			else {
				vAux = changeVaccine(vAux, tipoT, marcaT, dosisT, claveT, descT, fPrice);
				vAux = vOrigin;
				saveToFileVaccine();
				MessageBox(NULL, "Vacuna cambiada", "Yeih", MB_ICONINFORMATION);
			}
		}

	}break;
	case WM_CLOSE: {
		HWND hLogin = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_LOGIN_USER), NULL, fLogin);
		ShowWindow(hLogin, SW_SHOW);
		DestroyWindow(hwnd);
	}
				 break;
	case WM_DESTROY:
		break;
	}
	return FALSE;
}

BOOL CALLBACK fDeletePerson(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
	switch (msg) {
	case WM_INITDIALOG: {
		imprPerson(hwnd, LB_DELETE_PERSON);
		HWND btnOk = GetDlgItem(hwnd, BTN_OK_PERSONDELETE);
		EnableWindow(btnOk, false);
	}break;
	case WM_COMMAND: {
		if (LOWORD(wparam) == MENU_PERSONAS_REGISTRO && HIWORD(wparam) == BN_CLICKED) {
			HWND hRegisterPerson = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_REG_PERSON), NULL, fRegisterPerson);
			ShowWindow(hRegisterPerson, SW_SHOW);
			DestroyWindow(hwnd);
		}
		else if (LOWORD(wparam) == MENU_VACUNAS_REGISTRO && HIWORD(wparam) == BN_CLICKED) {
			HWND hRegistroVaccine = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_RE_VACUNA), NULL, fRegisterVaccine);
			ShowWindow(hRegistroVaccine, SW_SHOW);
			DestroyWindow(hwnd);
		}
		else if (LOWORD(wparam) == MENU_PANTALLAPRINCIPAL && HIWORD(wparam) == BN_CLICKED) {
			HWND hPrincipal = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_PRINCIPAL), NULL, fPrincipal);
			ShowWindow(hPrincipal, SW_SHOW);
			DestroyWindow(hwnd);
		}
		else if (LOWORD(wparam) == MENU_VACUNAS_BAJA && HIWORD(wparam) == BN_CLICKED) {
			HWND hDeleteVaccine = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_DELETE_VACUNA), NULL, fDeleteVaccine);
			ShowWindow(hDeleteVaccine, SW_SHOW);
			DestroyWindow(hwnd);
		}
		else if (LOWORD(wparam) == MENU_VACUNAS_CAMBIO && HIWORD(wparam) == BN_CLICKED) {
			HWND hChangeVaccine = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_CHANGE_VACCINE), NULL, fChangeVaccine);
			ShowWindow(hChangeVaccine, SW_SHOW);
			DestroyWindow(hwnd);
		}
		else if (LOWORD(wparam) == MENU_PERSONAS_CAMBIO && HIWORD(wparam) == BN_CLICKED) {
			HWND hChangePersonas = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_CHANGE_PERSON), NULL, fChangePerson);
			ShowWindow(hChangePersonas, SW_SHOW);
			DestroyWindow(hwnd);
		}
		else if (LOWORD(wparam) == MENU_CARNE_RE && HIWORD(wparam) == BN_CLICKED) {
			HWND hRegisterCarnet = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_REG_CARNET), NULL, fRegisterCarnet);
			ShowWindow(hRegisterCarnet, SW_SHOW);
			DestroyWindow(hwnd);
		}
		else if (LOWORD(wparam) == MENU_CARNE_BAJA && HIWORD(wparam) == BN_CLICKED) {
			HWND hDeleteCarnet = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_DELETE_CARNET), NULL, fDeleteCarnet);
			ShowWindow(hDeleteCarnet, SW_SHOW);
			DestroyWindow(hwnd);
		}
		else if (LOWORD(wparam) == MENU_CARNE_CAMBIO && HIWORD(wparam) == BN_CLICKED) {
			HWND hChangeCarnet = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_CHANGE_CARNET), NULL, fChangeCarnet);
			ShowWindow(hChangeCarnet, SW_SHOW);
			DestroyWindow(hwnd);
		}
		else if (LOWORD(wparam) == BTN_MENU_REPORT_NAME && HIWORD(wparam) == BN_CLICKED) {
			HWND hQuickSort = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_REPORTE_QUICKSORT), NULL, fReportQuickSort);
			ShowWindow(hQuickSort, SW_SHOW);
			DestroyWindow(hwnd);
		}
		else if (LOWORD(wparam) == BTN_MENU_REPORT_ID && HIWORD(wparam) == BN_CLICKED) {
			HWND hHeapSort = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_REPORTE_HEAPSORT), NULL, fReportHeapSort);
			ShowWindow(hHeapSort, SW_SHOW);
			DestroyWindow(hwnd);
		}
		else if (HIWORD(wparam) == LBN_DBLCLK) {
			showVariablesPersonDelete(hwnd);
			pAux = pOrigin;
			HWND btnOk = GetDlgItem(hwnd, BTN_OK_PERSONDELETE);
			EnableWindow(btnOk, true);
		}
		else if (LOWORD(wparam) == BTN_OK_PERSONDELETE && HIWORD(wparam) == BN_CLICKED) {
			string searchPersona = getHwndText(hwnd, TXT_CURP_PERSONDELETE);
			if (searchPersona.compare("-1") == 0) {
				MessageBox(NULL, "Seleccione la persona a eliminar", "Error", MB_ICONERROR);
				break;
			}
			foundedPersona = pAux = searchPerson(searchPersona, pAux);
			if (foundedPersona == NULL) {
				MessageBox(NULL, "Persona no encontrada", "Error", MB_ICONERROR);
				pAux = pOrigin;
				break;
			}
			else {
				borrarPerson();
				saveToFilePerson();
				MessageBox(NULL, "Persona eliminada", "Yeih", MB_ICONINFORMATION);
			}
		}

	}break;
	case WM_CLOSE: {
		HWND hLogin = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_LOGIN_USER), NULL, fLogin);
		ShowWindow(hLogin, SW_SHOW);
		DestroyWindow(hwnd);
	}
	 break;
	case WM_DESTROY:
		break;
	}
	return FALSE;
}

BOOL CALLBACK fChangePerson(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
	switch (msg) {
	case WM_INITDIALOG: {
		imprPerson(hwnd, LB_CHANGE_PERSON);
		cbComboCivil = GetDlgItem(hwnd, CB_CIVIL_CHANGEPERSON);
		cbComboSexo = GetDlgItem(hwnd, CB_SEXO_CHANGEPERSON);
		cbComboPerfil = GetDlgItem(hwnd, CB_PERFIL_CHANGEPERSON);
		cbComboIndetiti = GetDlgItem(hwnd, CB_IDENTIDAD_CHANGEPERSON);
		SendMessage(cbComboCivil, CB_ADDSTRING, NULL, (LPARAM)"Escoga una opcion...");
		SendMessage(cbComboCivil, CB_ADDSTRING, NULL, (LPARAM)"Soltero(a)");
		SendMessage(cbComboCivil, CB_ADDSTRING, NULL, (LPARAM)"Casado(a)");
		SendMessage(cbComboCivil, CB_ADDSTRING, NULL, (LPARAM)"Divorciado(a)");
		SendMessage(cbComboCivil, CB_ADDSTRING, NULL, (LPARAM)"Viudo(a)");
		SendMessage(cbComboSexo, CB_ADDSTRING, NULL, (LPARAM)"Escoga una opcion...");
		SendMessage(cbComboSexo, CB_ADDSTRING, NULL, (LPARAM)"Masculino");
		SendMessage(cbComboSexo, CB_ADDSTRING, NULL, (LPARAM)"Femenino");
		SendMessage(cbComboSexo, CB_ADDSTRING, NULL, (LPARAM)"Otro");
		SendMessage(cbComboPerfil, CB_ADDSTRING, NULL, (LPARAM)"Escoga una opcion...");
		SendMessage(cbComboPerfil, CB_ADDSTRING, NULL, (LPARAM)"Ninguno");
		SendMessage(cbComboPerfil, CB_ADDSTRING, NULL, (LPARAM)"PersonaMayor");
		SendMessage(cbComboPerfil, CB_ADDSTRING, NULL, (LPARAM)"Embarazada");
		SendMessage(cbComboPerfil, CB_ADDSTRING, NULL, (LPARAM)"Enfermedad");
		SendMessage(cbComboIndetiti, CB_ADDSTRING, NULL, (LPARAM)"Escoga una opcion...");
		SendMessage(cbComboIndetiti, CB_ADDSTRING, NULL, (LPARAM)"INE");
		SendMessage(cbComboIndetiti, CB_ADDSTRING, NULL, (LPARAM)"ACTA");
		SendMessage(cbComboIndetiti, CB_ADDSTRING, NULL, (LPARAM)"Otro");
		SendMessage(cbComboCivil, CB_SETCURSEL, 0, NULL);
		SendMessage(cbComboSexo, CB_SETCURSEL, 0, NULL);
		SendMessage(cbComboPerfil, CB_SETCURSEL, 0, NULL);
		SendMessage(cbComboIndetiti, CB_SETCURSEL, 0, NULL);
		HWND btnOk = GetDlgItem(hwnd, BTN_OK_PERSONCHANGE);
		EnableWindow(btnOk, false);
	}break;
	case WM_COMMAND: {
		if (LOWORD(wparam) == MENU_PERSONAS_REGISTRO && HIWORD(wparam) == BN_CLICKED) {
			HWND hRegisterPerson = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_REG_PERSON), NULL, fRegisterPerson);
			ShowWindow(hRegisterPerson, SW_SHOW);
			DestroyWindow(hwnd);
		}
		else if (LOWORD(wparam) == MENU_VACUNAS_REGISTRO && HIWORD(wparam) == BN_CLICKED) {
			HWND hRegistroVaccine = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_RE_VACUNA), NULL, fRegisterVaccine);
			ShowWindow(hRegistroVaccine, SW_SHOW);
			DestroyWindow(hwnd);
		}
		else if (LOWORD(wparam) == MENU_PANTALLAPRINCIPAL && HIWORD(wparam) == BN_CLICKED) {
			HWND hPrincipal = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_PRINCIPAL), NULL, fPrincipal);
			ShowWindow(hPrincipal, SW_SHOW);
			DestroyWindow(hwnd);
		}
		else if (LOWORD(wparam) == MENU_VACUNAS_BAJA && HIWORD(wparam) == BN_CLICKED) {
			HWND hDeleteVaccine = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_DELETE_VACUNA), NULL, fDeleteVaccine);
			ShowWindow(hDeleteVaccine, SW_SHOW);
			DestroyWindow(hwnd);
		}
		else if (LOWORD(wparam) == MENU_VACUNAS_CAMBIO && HIWORD(wparam) == BN_CLICKED) {
			HWND hChangeVaccine = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_CHANGE_VACCINE), NULL, fChangeVaccine);
			ShowWindow(hChangeVaccine, SW_SHOW);
			DestroyWindow(hwnd);
		}
		else if (LOWORD(wparam) == MENU_PERSONAS_BAJA && HIWORD(wparam) == BN_CLICKED) {
			HWND hDeletePersonas = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_BAJA_PERSONAS), NULL, fDeletePerson);
			ShowWindow(hDeletePersonas, SW_SHOW);
			DestroyWindow(hwnd);
		}
		else if (LOWORD(wparam) == MENU_CARNE_RE && HIWORD(wparam) == BN_CLICKED) {
			HWND hRegisterCarnet = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_REG_CARNET), NULL, fRegisterCarnet);
			ShowWindow(hRegisterCarnet, SW_SHOW);
			DestroyWindow(hwnd);
		}
		else if (LOWORD(wparam) == MENU_CARNE_BAJA && HIWORD(wparam) == BN_CLICKED) {
			HWND hDeleteCarnet = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_DELETE_CARNET), NULL, fDeleteCarnet);
			ShowWindow(hDeleteCarnet, SW_SHOW);
			DestroyWindow(hwnd);
		}
		else if (LOWORD(wparam) == MENU_CARNE_CAMBIO && HIWORD(wparam) == BN_CLICKED) {
			HWND hChangeCarnet = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_CHANGE_CARNET), NULL, fChangeCarnet);
			ShowWindow(hChangeCarnet, SW_SHOW);
			DestroyWindow(hwnd);
		}
		else if (LOWORD(wparam) == BTN_MENU_REPORT_NAME && HIWORD(wparam) == BN_CLICKED) {
			HWND hQuickSort = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_REPORTE_QUICKSORT), NULL, fReportQuickSort);
			ShowWindow(hQuickSort, SW_SHOW);
			DestroyWindow(hwnd);
		}
		else if (LOWORD(wparam) == BTN_MENU_REPORT_ID && HIWORD(wparam) == BN_CLICKED) {
			HWND hHeapSort = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_REPORTE_HEAPSORT), NULL, fReportHeapSort);
			ShowWindow(hHeapSort, SW_SHOW);
			DestroyWindow(hwnd);
		}
		else if (HIWORD(wparam) == LBN_DBLCLK) {

			showVariablesPersonChange(hwnd);
			pAux = pOrigin;
			HWND btnOk = GetDlgItem(hwnd, BTN_OK_PERSONCHANGE);
			EnableWindow(btnOk, true);
		}
		
		else if (LOWORD(wparam) == BTN_OK_PERSONCHANGE && HIWORD(wparam) == BN_CLICKED) {
			string apT = getHwndText(hwnd, TXT_AP_PERSONCHANGE);
			string amT = getHwndText(hwnd, TXT_AM_PERSONCHANGE);
			string nameT = getHwndText(hwnd, TXT_NAME_PERSONCHANGE);
			string curpT = getHwndText(hwnd, TXT_CURP_PERSONCHANGE);
			string rfcT = getHwndText(hwnd, TXT_RFC_PERSONCHANGE);
			string calleT = getHwndText(hwnd, TXT_CALLE_PERSONCHANGE);
			string coloniaT = getHwndText(hwnd, TXT_COLONIA_PERSONCHANGE);
			string ciudadT = getHwndText(hwnd, TXT_CIUDAD_PERSONCHANGE);
			string estadoT = getHwndText(hwnd, TXT_ESTADO_PERSONCHANGE);
			string telefoT = getHwndText(hwnd, TXT_TELEFO_PERSONCHANGE);
			string grupoT = getHwndText(hwnd, TXT_GRUPO_PERSONCHANGE);
			HWND fecha = GetDlgItem(hwnd, DT_FECHA_CHANGEPERSON);
			int iFecLength = GetWindowTextLength(fecha) + 1;
			char cFecha[15];
			GetWindowText(fecha, cFecha, iFecLength);
			string fechaDTP(cFecha);

			int index = SendMessage(cbComboCivil, CB_GETCURSEL, NULL, NULL);
			int index2 = SendMessage(cbComboSexo, CB_GETCURSEL, NULL, NULL);
			int index3 = SendMessage(cbComboPerfil, CB_GETCURSEL, NULL, NULL);
			int index4 = SendMessage(cbComboIndetiti, CB_GETCURSEL, NULL, NULL);

			if (index < 1) {
				MessageBox(NULL, "No selecciono el estado civil", "Error", MB_ICONERROR);
				break;
			}
			else {
				int length = GetWindowTextLength(cbComboCivil);
				GetWindowText(cbComboCivil, estadoCivilchar, length + 1);
			}
			if (index2 < 1) {
				MessageBox(NULL, "No selecciono el sexo", "Error", MB_ICONERROR);
				break;
			}
			else {
				int length = GetWindowTextLength(cbComboSexo);
				GetWindowText(cbComboSexo, sexoChar, length + 1);
			}
			if (index3 < 1) {
				MessageBox(NULL, "No selecciono el perfil de riesgo", "Error", MB_ICONERROR);
				break;
			}
			else {
				int length = GetWindowTextLength(cbComboPerfil);
				GetWindowText(cbComboPerfil, perfilChar, length + 1);
			}
			if (index4 < 1) {
				MessageBox(NULL, "No selecciono el documento de identidad", "Error", MB_ICONERROR);
				break;
			}
			else {
				int length = GetWindowTextLength(cbComboIndetiti);
				GetWindowText(cbComboIndetiti, identitiChar, length + 1);
			}
			string civil = estadoCivilchar;
			string sexo = sexoChar;
			string perfil = perfilChar;
			string identiti = identitiChar;
			wstring curpWstring = wstring(curpT.begin(), curpT.end());
			wstring rfcWstring = wstring(rfcT.begin(), rfcT.end());
			const wchar_t* checarCurp;
			const wchar_t* checarRFC;
			checarCurp = curpWstring.c_str();
			checarRFC = rfcWstring.c_str();
			if (wcschr(checarCurp, ' ') != nullptr) {
				MessageBox(NULL, "El CURP tiene espacios en blanco", "Error", MB_ICONERROR);
				break;
			}
			if (wcschr(checarRFC, ' ') != nullptr) {
				MessageBox(NULL, "El RFC tiene espacios en blanco", "Error", MB_ICONERROR);
				break;
			}

			if (apT.compare("-1") == 0 || amT.compare("-1") == 0 || nameT.compare("-1") == 0 || curpT.compare("-1") == 0 || rfcT.compare("-1") == 0 || calleT.compare("-1") == 0 || coloniaT.compare("-1") == 0 || ciudadT.compare("-1") == 0 || estadoT.compare("-1") == 0 || telefoT.compare("-1") == 0 || grupoT.compare("-1") == 0) {
				MessageBox(NULL, "LLene los espacios con la nueva informacion", "Error", MB_ICONERROR);
				break;
			}

			foundedPersona = pAux = searchPersonWithId(idPersonFounded, pAux);
			if (foundedPersona == NULL) {
				MessageBox(NULL, "Persona no encontrada", "Error", MB_ICONERROR);
				pAux = pOrigin;
				break;
			}
			/*bool checkDouble = searchPersonCopy2(curpT, rfcT, pAux);
			if (checkDouble == true) {
				MessageBox(NULL, "CURP o RFC repetidos", "Error", MB_ICONERROR);
				pAux = pOrigin;
				break;
			}*/
			else {
				pAux = changePerson (pAux, apT, amT, nameT, curpT, rfcT, fechaDTP, calleT, coloniaT, ciudadT, estadoT, civil, telefoT, sexo, grupoT, perfil, identiti);
				pAux = pOrigin;
				saveToFilePerson();
				MessageBox(NULL, "Persona cambiada", "Yeih", MB_ICONINFORMATION);
			}
		}
		else if (LOWORD(wparam) == BTN_LOADNEWIMAGE_CHANGEPERSON && HIWORD(wparam) == BN_CLICKED) {

			OPENFILENAME ofn;
			ZeroMemory(&ofn, sizeof(OPENFILENAME));
			char cDirFile[MAX_PATH] = "";
			ofn.hwndOwner = hwnd;
			ofn.lpstrFile = cDirFile;
			ofn.lStructSize = sizeof(OPENFILENAME);
			ofn.nMaxFile = MAX_PATH;
			ofn.lpstrDefExt = "txt";
			ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_NOCHANGEDIR;
			ofn.lpstrFilter = "Todos los archivos\0*.*\0";

			if (GetOpenFileName(&ofn)) {

				HWND hPBImagen = GetDlgItem(hwnd, BM_IMAGE_PERSONCHANGE);
				HBITMAP hImagePerson = (HBITMAP)LoadImage(NULL, cDirFile, IMAGE_BITMAP, 100, 100, LR_LOADFROMFILE);
				SendMessage(hPBImagen, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hImagePerson);
				pImageTempPerson = cDirFile;
			}
		}

	}break;
	case WM_CLOSE: {
		HWND hLogin = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_LOGIN_USER), NULL, fLogin);
		ShowWindow(hLogin, SW_SHOW);
		DestroyWindow(hwnd);
	}
				 break;
	case WM_DESTROY:
		break;
	}
	return FALSE;
}

BOOL CALLBACK fRegisterCarnet(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
	switch (msg) {
	case WM_INITDIALOG: {
		imprPerson(hwnd, LB_CURP_RE_CARNET);
		imprVaccine(hwnd, LB_CLAVE_RE_CARNET);
		HWND btnOk = GetDlgItem(hwnd, BTN_OK_RE_CARNET);
		EnableWindow(btnOk, false);
		HWND hIdCarnet = GetDlgItem(hwnd, TXT_ID_RE_CARNET);
		char tempId[10];
		_itoa_s(globalIdCarnet, tempId, 10);
		SetWindowText(hIdCarnet, tempId);
		time(&actualTime);
		tiempo = localtime(&actualTime);
		check1 = false, check2 = false;
	}break;
	case WM_COMMAND: {
		if (LOWORD(wparam) == MENU_PERSONAS_REGISTRO && HIWORD(wparam) == BN_CLICKED) {
			HWND hRegisterPerson = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_REG_PERSON), NULL, fRegisterPerson);
			ShowWindow(hRegisterPerson, SW_SHOW);
			DestroyWindow(hwnd);
		}
		else if (LOWORD(wparam) == MENU_PANTALLAPRINCIPAL && HIWORD(wparam) == BN_CLICKED) {
			HWND hPrincipal = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_PRINCIPAL), NULL, fPrincipal);
			ShowWindow(hPrincipal, SW_SHOW);
			DestroyWindow(hwnd);
		}
		else if (LOWORD(wparam) == MENU_VACUNAS_BAJA && HIWORD(wparam) == BN_CLICKED) {
			HWND hDeleteVaccine = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_DELETE_VACUNA), NULL, fDeleteVaccine);
			ShowWindow(hDeleteVaccine, SW_SHOW);
			DestroyWindow(hwnd);
		}
		else if (LOWORD(wparam) == MENU_VACUNAS_CAMBIO && HIWORD(wparam) == BN_CLICKED) {
			HWND hChangeVaccine = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_CHANGE_VACCINE), NULL, fChangeVaccine);
			ShowWindow(hChangeVaccine, SW_SHOW);
			DestroyWindow(hwnd);
		}
		else if (LOWORD(wparam) == MENU_PERSONAS_BAJA && HIWORD(wparam) == BN_CLICKED) {
			HWND hDeletePersonas = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_BAJA_PERSONAS), NULL, fDeletePerson);
			ShowWindow(hDeletePersonas, SW_SHOW);
			DestroyWindow(hwnd);
		}
		else if (LOWORD(wparam) == MENU_PERSONAS_CAMBIO && HIWORD(wparam) == BN_CLICKED) {
			HWND hChangePersonas = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_CHANGE_PERSON), NULL, fChangePerson);
			ShowWindow(hChangePersonas, SW_SHOW);
			DestroyWindow(hwnd);
		}
		else if (LOWORD(wparam) == MENU_VACUNAS_REGISTRO && HIWORD(wparam) == BN_CLICKED) {
			HWND hRegistroVaccine = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_RE_VACUNA), NULL, fRegisterVaccine);
			ShowWindow(hRegistroVaccine, SW_SHOW);
			DestroyWindow(hwnd);
		}
		else if (LOWORD(wparam) == MENU_CARNE_BAJA && HIWORD(wparam) == BN_CLICKED) {
			HWND hDeleteCarnet = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_DELETE_CARNET), NULL, fDeleteCarnet);
			ShowWindow(hDeleteCarnet, SW_SHOW);
			DestroyWindow(hwnd);
		}
		else if (LOWORD(wparam) == MENU_CARNE_CAMBIO && HIWORD(wparam) == BN_CLICKED) {
			HWND hChangeCarnet = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_CHANGE_CARNET), NULL, fChangeCarnet);
			ShowWindow(hChangeCarnet, SW_SHOW);
			DestroyWindow(hwnd);
		}
		else if (LOWORD(wparam) == BTN_MENU_REPORT_NAME && HIWORD(wparam) == BN_CLICKED) {
			HWND hQuickSort = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_REPORTE_QUICKSORT), NULL, fReportQuickSort);
			ShowWindow(hQuickSort, SW_SHOW);
			DestroyWindow(hwnd);
		}
		else if (LOWORD(wparam) == BTN_MENU_REPORT_ID && HIWORD(wparam) == BN_CLICKED) {
			HWND hHeapSort = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_REPORTE_HEAPSORT), NULL, fReportHeapSort);
			ShowWindow(hHeapSort, SW_SHOW);
			DestroyWindow(hwnd);
		}
		else if (LOWORD(wparam) == LB_CURP_RE_CARNET && HIWORD(wparam) == LBN_DBLCLK) {
			showVariablesCarnetCurpRe(hwnd);
			check1 = true;
			cAux = cOrigin;
			habilitarBoton(check1, check2, hwnd);
		}
		else if (LOWORD(wparam) == LB_CLAVE_RE_CARNET && HIWORD(wparam) == LBN_DBLCLK) {
			showVariablesCarnetClaveRe(hwnd);
			fechaDosisVacuna(hwnd, TXT_FECHAVACU1_RE_CARNET, TXT_FECHAVACU2_RE_CARNET);
			check2 = true;
			cAux = cOrigin;
			habilitarBoton(check1, check2, hwnd);
		}
		else if (LOWORD(wparam) == BTN_OK_RE_CARNET && HIWORD(wparam) == BN_CLICKED) {
			string curpCarnet = getHwndText(hwnd, TXT_CURP_RE_CARNET);
			string vacunaCarnet = getHwndText(hwnd, TXT_MARCA_RE_CARNET);
			string dosisCarnet = getHwndText(hwnd, TXT_DOSIS_RE_CARNET);
			string fechaDosisCar = getHwndText(hwnd, TXT_FECHAVACU1_RE_CARNET);
			string fechaDosisCar2 = getHwndText(hwnd, TXT_FECHAVACU2_RE_CARNET);
			string loteMarca = getHwndText(hwnd, TXT_TIPO_RE_CARNET);
			string centroVacu = getHwndText(hwnd, TXT_CENTRO_RE_CARNET);
			string apPersonCar = getHwndText(hwnd, TXT_AP_RE_CARNET);
			string amPersonCar = getHwndText(hwnd, TXT_AM_RE_CARNET);
			string namePersonCar = getHwndText(hwnd, TXT_NAME_RE_CARNET);
			string RFCCAR = getHwndText(hwnd, TXT_RFC_RE_CARNET);
			string fechaNaciCar = getHwndText(hwnd, TXT_FECHA_RE_CARNET);
			string calleCar = getHwndText(hwnd, TXT_CALLE_RE_CARNET);
			string coloniaCar = getHwndText(hwnd, TXT_COLONIA_RE_CARNET);
			string estadoCar = getHwndText(hwnd, TXT_ESTADO_RE_CARNET);
			string estadoCivilCar = getHwndText(hwnd, TXT_CIVIL_RE_CARNET);
			string telefonoCar = getHwndText(hwnd, TXT_TELEFO_RE_CARNET);
			string ciudadCar = getHwndText(hwnd, TXT_CIUDAD_RE_CARNET);
			string sexoCar = getHwndText(hwnd, TXT_SEXO_RE_CARNET);
			string grupoOcupCar = getHwndText(hwnd, TXT_GRUPO_RE_CARNET);
			string perfilRiesCar = getHwndText(hwnd, TXT_PERFIL_RE_CARNET);
			string identitiStringCar = getHwndText(hwnd, TXT_IDENTITI_RE_CARNET);
			string claveVaccineCar = getHwndText(hwnd, TXT_CLAVE_RE_CARNET);
			string descripcionCar = getHwndText(hwnd, TXT_DES_RE_CARNET);
			string precioCar = getHwndText(hwnd, TXT_PRECIO_RE_CARNET);

			char cDesCar[50];
			float fPriceCar = atof(precioCar.c_str());
			strcpy_s(cDesCar, descripcionCar.c_str());

			if (curpCarnet.compare("-1") == 0 || vacunaCarnet.compare("-1") == 0 || dosisCarnet.compare("-1") == 0 || fechaDosisCar.compare("-1") == 0 || loteMarca.compare("-1") == 0 || centroVacu.compare("-1") == 0) {
				MessageBox(NULL, "Campos incompletos", "Error", MB_ICONERROR);
				break;
			}
			if (saveCarnet(curpCarnet, vacunaCarnet, dosisCarnet, fechaDosisCar, fechaDosisCar2, loteMarca, centroVacu, apPersonCar,amPersonCar,namePersonCar,RFCCAR, fechaNaciCar, calleCar, coloniaCar, estadoCar, estadoCivilCar, telefonoCar, ciudadCar, sexoCar, grupoOcupCar, perfilRiesCar, identitiStringCar, claveVaccineCar, descripcionCar, fPriceCar, globalIdCarnet++) == false) {
				--globalIdCarnet;
				MessageBox(NULL, "Carnet de persona ya existente", "Error", MB_ICONERROR);
			}
			else {
				saveMaxIdCarnet();
				saveToFileCarnet();
				MessageBox(NULL, "Carnet registrado con exito", "EXITO", MB_ICONINFORMATION);
			}
			clearHwnd(hwnd, TXT_CURP_RE_CARNET);
			clearHwnd(hwnd, TXT_MARCA_RE_CARNET);
			clearHwnd(hwnd, TXT_DOSIS_RE_CARNET);
			clearHwnd(hwnd, TXT_FECHAVACU1_RE_CARNET);
			clearHwnd(hwnd, TXT_TIPO_RE_CARNET);
			clearHwnd(hwnd, TXT_CENTRO_RE_CARNET);
		}
		
	}break;
	case WM_CLOSE: {
		HWND hLogin = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_LOGIN_USER), NULL, fLogin);
		ShowWindow(hLogin, SW_SHOW);
		DestroyWindow(hwnd);
	}
				 break;
	case WM_DESTROY:
		break;
	}
	return FALSE;
}

BOOL CALLBACK fDeleteCarnet(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
	switch (msg) {
	case WM_INITDIALOG: {
	}break;
	case WM_COMMAND: {
		if (LOWORD(wparam) == MENU_PERSONAS_REGISTRO && HIWORD(wparam) == BN_CLICKED) {
			HWND hRegisterPerson = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_REG_PERSON), NULL, fRegisterPerson);
			ShowWindow(hRegisterPerson, SW_SHOW);
			DestroyWindow(hwnd);
		}
		else if (LOWORD(wparam) == MENU_PANTALLAPRINCIPAL && HIWORD(wparam) == BN_CLICKED) {
			HWND hPrincipal = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_PRINCIPAL), NULL, fPrincipal);
			ShowWindow(hPrincipal, SW_SHOW);
			DestroyWindow(hwnd);
		}
		else if (LOWORD(wparam) == MENU_VACUNAS_REGISTRO && HIWORD(wparam) == BN_CLICKED) {
			HWND hRegistroVaccine = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_RE_VACUNA), NULL, fRegisterVaccine);
			ShowWindow(hRegistroVaccine, SW_SHOW);
			DestroyWindow(hwnd);
		}
		else if (LOWORD(wparam) == MENU_VACUNAS_BAJA && HIWORD(wparam) == BN_CLICKED) {
			HWND hDeleteVaccine = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_DELETE_VACUNA), NULL, fDeleteVaccine);
			ShowWindow(hDeleteVaccine, SW_SHOW);
			DestroyWindow(hwnd);
		}
		else if (LOWORD(wparam) == MENU_VACUNAS_CAMBIO && HIWORD(wparam) == BN_CLICKED) {
			HWND hChangeVaccine = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_CHANGE_VACCINE), NULL, fChangeVaccine);
			ShowWindow(hChangeVaccine, SW_SHOW);
			DestroyWindow(hwnd);
		}
		else if (LOWORD(wparam) == MENU_PERSONAS_BAJA && HIWORD(wparam) == BN_CLICKED) {
			HWND hDeletePersonas = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_BAJA_PERSONAS), NULL, fDeletePerson);
			ShowWindow(hDeletePersonas, SW_SHOW);
			DestroyWindow(hwnd);
		}
		else if (LOWORD(wparam) == MENU_PERSONAS_CAMBIO && HIWORD(wparam) == BN_CLICKED) {
			HWND hChangePersonas = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_CHANGE_PERSON), NULL, fChangePerson);
			ShowWindow(hChangePersonas, SW_SHOW);
			DestroyWindow(hwnd);
		}
		else if (LOWORD(wparam) == MENU_CARNE_RE && HIWORD(wparam) == BN_CLICKED) {
			HWND hRegisterCarnet = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_REG_CARNET), NULL, fRegisterCarnet);
			ShowWindow(hRegisterCarnet, SW_SHOW);
			DestroyWindow(hwnd);
		}
		else if (LOWORD(wparam) == MENU_CARNE_CAMBIO && HIWORD(wparam) == BN_CLICKED) {
			HWND hChangeCarnet = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_CHANGE_CARNET), NULL, fChangeCarnet);
			ShowWindow(hChangeCarnet, SW_SHOW);
			DestroyWindow(hwnd);
		}
		else if (LOWORD(wparam) == BTN_MENU_REPORT_NAME && HIWORD(wparam) == BN_CLICKED) {
			HWND hQuickSort = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_REPORTE_QUICKSORT), NULL, fReportQuickSort);
			ShowWindow(hQuickSort, SW_SHOW);
			DestroyWindow(hwnd);
		}
		else if (LOWORD(wparam) == BTN_MENU_REPORT_ID && HIWORD(wparam) == BN_CLICKED) {
			HWND hHeapSort = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_REPORTE_HEAPSORT), NULL, fReportHeapSort);
			ShowWindow(hHeapSort, SW_SHOW);
			DestroyWindow(hwnd);
		}
		else if (LOWORD(wparam) == BTN_BINARIO_DELETE && HIWORD(wparam) == BN_CLICKED) {
			string binario = getHwndText(hwnd, TXT_BINARIA_DELETE);
			int bin = atoi(binario.c_str());
			if (binario.compare("-1") == 0) {
				MessageBox(NULL, "Escriba un ID", "Error", MB_ICONERROR);
				break;
			}
			carnetFounded = cAux = busquedaBinaria(cAux, bin);
			if (carnetFounded == NULL) {
				MessageBox(NULL, "Carnet no encontrado", "Error", MB_ICONERROR);
				cAux = cOrigin;
				break;
			}
			else {
				showVariablesCarnetDelete(hwnd);
				cAux = cOrigin;
			}
		}
		else if (LOWORD(wparam) == BTN_OK_DELETE_CARNET && HIWORD(wparam) == BN_CLICKED) {
			string binario = getHwndText(hwnd, TXT_ID_DELETE_CARNET);
			int bin = atoi(binario.c_str());
			if (binario.compare("-1") == 0) {
				MessageBox(NULL, "Seleccione el carnet a eliminar", "Error", MB_ICONERROR);
				break;
			}
			carnetFounded = cAux = busquedaBinaria(cAux, bin);
			if (carnetFounded == NULL) {
				MessageBox(NULL, "Carnet no encontrado", "Error", MB_ICONERROR);
				cAux = cOrigin;
				break;
			}
			else {
				borrarCarnet();
				saveToFileCarnet();
				MessageBox(NULL, "Carnet eliminado", "Yeih", MB_ICONINFORMATION);
			}
		}
	}break;
	case WM_CLOSE: {
		HWND hLogin = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_LOGIN_USER), NULL, fLogin);
		ShowWindow(hLogin, SW_SHOW);
		DestroyWindow(hwnd);
	}
				 break;
	case WM_DESTROY:
		break;
	}
	return FALSE;
}

BOOL CALLBACK fChangeCarnet(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
	switch (msg) {
	case WM_INITDIALOG: {
		imprPerson(hwnd, LB_CURP_CHANGE_CARNET);
		imprVaccine(hwnd, LB_CLAVE_CHANGE_CARNET);
		HWND btnOk = GetDlgItem(hwnd, BTN_OK_CHANGE_CARNET);
		EnableWindow(btnOk, false);
		time(&actualTime);
		tiempo = localtime(&actualTime);
	}break;
	case WM_COMMAND: {
		if (LOWORD(wparam) == MENU_PERSONAS_REGISTRO && HIWORD(wparam) == BN_CLICKED) {
			HWND hRegisterPerson = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_REG_PERSON), NULL, fRegisterPerson);
			ShowWindow(hRegisterPerson, SW_SHOW);
			DestroyWindow(hwnd);
		}
		else if (LOWORD(wparam) == MENU_PANTALLAPRINCIPAL && HIWORD(wparam) == BN_CLICKED) {
			HWND hPrincipal = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_PRINCIPAL), NULL, fPrincipal);
			ShowWindow(hPrincipal, SW_SHOW);
			DestroyWindow(hwnd);
		}
		else if (LOWORD(wparam) == MENU_VACUNAS_REGISTRO && HIWORD(wparam) == BN_CLICKED) {
			HWND hRegistroVaccine = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_RE_VACUNA), NULL, fRegisterVaccine);
			ShowWindow(hRegistroVaccine, SW_SHOW);
			DestroyWindow(hwnd);
		}
		else if (LOWORD(wparam) == MENU_VACUNAS_BAJA && HIWORD(wparam) == BN_CLICKED) {
			HWND hDeleteVaccine = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_DELETE_VACUNA), NULL, fDeleteVaccine);
			ShowWindow(hDeleteVaccine, SW_SHOW);
			DestroyWindow(hwnd);
		}
		else if (LOWORD(wparam) == MENU_VACUNAS_CAMBIO && HIWORD(wparam) == BN_CLICKED) {
			HWND hChangeVaccine = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_CHANGE_VACCINE), NULL, fChangeVaccine);
			ShowWindow(hChangeVaccine, SW_SHOW);
			DestroyWindow(hwnd);
		}
		else if (LOWORD(wparam) == MENU_PERSONAS_BAJA && HIWORD(wparam) == BN_CLICKED) {
			HWND hDeletePersonas = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_BAJA_PERSONAS), NULL, fDeletePerson);
			ShowWindow(hDeletePersonas, SW_SHOW);
			DestroyWindow(hwnd);
		}
		else if (LOWORD(wparam) == MENU_PERSONAS_CAMBIO && HIWORD(wparam) == BN_CLICKED) {
			HWND hChangePersonas = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_CHANGE_PERSON), NULL, fChangePerson);
			ShowWindow(hChangePersonas, SW_SHOW);
			DestroyWindow(hwnd);
		}
		else if (LOWORD(wparam) == MENU_CARNE_RE && HIWORD(wparam) == BN_CLICKED) {
			HWND hRegisterCarnet = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_REG_CARNET), NULL, fRegisterCarnet);
			ShowWindow(hRegisterCarnet, SW_SHOW);
			DestroyWindow(hwnd);
		}
		else if (LOWORD(wparam) == MENU_CARNE_BAJA && HIWORD(wparam) == BN_CLICKED) {
			HWND hDeleteCarnet = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_DELETE_CARNET), NULL, fDeleteCarnet);
			ShowWindow(hDeleteCarnet, SW_SHOW);
			DestroyWindow(hwnd);
		}
		else if (LOWORD(wparam) == BTN_MENU_REPORT_NAME && HIWORD(wparam) == BN_CLICKED) {
			HWND hQuickSort = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_REPORTE_QUICKSORT), NULL, fReportQuickSort);
			ShowWindow(hQuickSort, SW_SHOW);
			DestroyWindow(hwnd);
		}
		else if (LOWORD(wparam) == BTN_MENU_REPORT_ID && HIWORD(wparam) == BN_CLICKED) {
			HWND hHeapSort = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_REPORTE_HEAPSORT), NULL, fReportHeapSort);
			ShowWindow(hHeapSort, SW_SHOW);
			DestroyWindow(hwnd);
		}
		else if (LOWORD(wparam) == LB_CURP_CHANGE_CARNET && HIWORD(wparam) == LBN_DBLCLK) {
			showVariablesCarnetCurpChange(hwnd);
			cAux = cOrigin;
		}
		else if (LOWORD(wparam) == LB_CLAVE_CHANGE_CARNET && HIWORD(wparam) == LBN_DBLCLK) {
			showVariablesCarnetClaveChange(hwnd);
			fechaDosisVacuna(hwnd, TXT_FECHAVACU1_CHANGE_CARNET, TXT_FECHAVACU2_CHANGE_CARNET);
			cAux = cOrigin;
		}
		else if (LOWORD(wparam) == BTN_BINARIO_CHANGE && HIWORD(wparam) == BN_CLICKED) {
			string binario = getHwndText(hwnd, TXT_BINARIA_CHANGE);
			int bin = atoi(binario.c_str());
			if (binario.compare("-1") == 0) {
				MessageBox(NULL, "Escriba un ID", "Error", MB_ICONERROR);
				break;
			}
			carnetFounded = cAux = busquedaBinaria(cAux, bin);
			if (carnetFounded == NULL) {
				MessageBox(NULL, "Carnet no encontrado", "Error", MB_ICONERROR);
				cAux = cOrigin;
				break;
			}
			else {
				showVariablesCarnetChange(hwnd);
				cAux = cOrigin;
				HWND btnOk = GetDlgItem(hwnd, BTN_OK_CHANGE_CARNET);
				EnableWindow(btnOk, true);
			}
		}
		else if (LOWORD(wparam) == BTN_OK_CHANGE_CARNET && HIWORD(wparam) == BN_CLICKED) {
			string curpCarnet = getHwndText(hwnd, TXT_CURP_CHANGE_CARNET);
			string vacunaCarnet = getHwndText(hwnd, TXT_MARCA_CHANGE_CARNET);
			string dosisCarnet = getHwndText(hwnd, TXT_DOSIS_CHANGE_CARNET);
			string fechaDosisCar = getHwndText(hwnd, TXT_FECHAVACU1_CHANGE_CARNET);
			string fechaDosisCar2 = getHwndText(hwnd, TXT_FECHAVACU2_CHANGE_CARNET);
			string loteMarca = getHwndText(hwnd, TXT_TIPO_CHANGE_CARNET);
			string centroVacu = getHwndText(hwnd, TXT_CENTRO_CHANGE_CARNET);
			string apPersonCar = getHwndText(hwnd, TXT_AP_CHANGE_CARNET);
			string amPersonCar = getHwndText(hwnd, TXT_AM_CHANGE_CARNET);
			string namePersonCar = getHwndText(hwnd, TXT_NAME_CHANGE_CARNET);
			string RFCCAR = getHwndText(hwnd, TXT_RFC_CHANGE_CARNET);
			string fechaNaciCar = getHwndText(hwnd, TXT_FECHA_CHANGE_CARNET);
			string calleCar = getHwndText(hwnd, TXT_CALLE_CHANGE_CARNET);
			string coloniaCar = getHwndText(hwnd, TXT_COLONIA_CHANGE_CARNET);
			string estadoCar = getHwndText(hwnd, TXT_ESTADO_CHANGE_CARNET);
			string estadoCivilCar = getHwndText(hwnd, TXT_CIVIL_CHANGE_CARNET);
			string telefonoCar = getHwndText(hwnd, TXT_TELEFO_CHANGE_CARNET);
			string ciudadCar = getHwndText(hwnd, TXT_CIUDAD_CHANGE_CARNET);
			string sexoCar = getHwndText(hwnd, TXT_SEXO_CHANGE_CARNET);
			string grupoOcupCar = getHwndText(hwnd, TXT_GRUPO_CHANGE_CARNET);
			string perfilRiesCar = getHwndText(hwnd, TXT_PERFIL_CHANGE_CARNET);
			string identitiStringCar = getHwndText(hwnd, TXT_IDENTITI_CHANGE_CARNET);
			string claveVaccineCar = getHwndText(hwnd, TXT_CLAVE_CHANGE_CARNET);
			string descripcionCar = getHwndText(hwnd, TXT_DES_CHANGE_CARNET);
			string precioCar = getHwndText(hwnd, TXT_PRECIO_CHANGE_CARNET);
			char cDesCar[50];
			float fPriceCar = atof(precioCar.c_str());
			strcpy_s(cDesCar, descripcionCar.c_str());

			if (curpCarnet.compare("-1") == 0 || vacunaCarnet.compare("-1") == 0 || dosisCarnet.compare("-1") == 0 || fechaDosisCar.compare("-1") == 0 || loteMarca.compare("-1") == 0 || centroVacu.compare("-1") == 0) {
				MessageBox(NULL, "Campos incompletos", "Error", MB_ICONERROR);
				break;
			}
			string binario = getHwndText(hwnd, TXT_ID_CHANGE_CARNET);
			int bin = atoi(binario.c_str());
			if (binario.compare("-1") == 0) {
				MessageBox(NULL, "Seleccione el carnet a eliminar", "Error", MB_ICONERROR);
				break;
			}
			carnetFounded = cAux = busquedaBinaria(cAux, bin);
			if (carnetFounded == NULL) {
				MessageBox(NULL, "Carnet no encontrado", "Error", MB_ICONERROR);
				cAux = cOrigin;
				break;
			}
			else {
				cAux = changeCarnet(cAux, curpCarnet, vacunaCarnet, dosisCarnet, fechaDosisCar, fechaDosisCar2, loteMarca, centroVacu, apPersonCar, amPersonCar, namePersonCar, RFCCAR, fechaNaciCar, calleCar, coloniaCar, estadoCar, estadoCivilCar, telefonoCar, ciudadCar, sexoCar, grupoOcupCar, perfilRiesCar, identitiStringCar, claveVaccineCar, descripcionCar, fPriceCar);
				cAux = cOrigin;
				saveToFileCarnet();
				MessageBox(NULL, "Carnet cambiado", "Yeih", MB_ICONINFORMATION);
			}
			clearHwnd(hwnd, TXT_CURP_CHANGE_CARNET);
			clearHwnd(hwnd, TXT_MARCA_CHANGE_CARNET);
			clearHwnd(hwnd, TXT_DOSIS_CHANGE_CARNET);
			clearHwnd(hwnd, TXT_FECHAVACU1_CHANGE_CARNET);
			clearHwnd(hwnd, TXT_TIPO_CHANGE_CARNET);
			clearHwnd(hwnd, TXT_CENTRO_CHANGE_CARNET);
		}
	}break;
	case WM_CLOSE: {
		HWND hLogin = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_LOGIN_USER), NULL, fLogin);
		ShowWindow(hLogin, SW_SHOW);
		DestroyWindow(hwnd);
	}
				 break;
	case WM_DESTROY:
		break;
	}
	return FALSE;
}

BOOL CALLBACK fReportHeapSort(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
	switch (msg) {
	case WM_INITDIALOG: {
		int cant = 0;
		int infoHeap[259];
		reportHeapSort(cant, infoHeap, hwnd, LB_HEAPSORT_REPORT);
	}break;
	case WM_COMMAND: {
		if (LOWORD(wparam) == MENU_PERSONAS_REGISTRO && HIWORD(wparam) == BN_CLICKED) {
			HWND hRegisterPerson = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_REG_PERSON), NULL, fRegisterPerson);
			ShowWindow(hRegisterPerson, SW_SHOW);
			DestroyWindow(hwnd);
		}
		else if (LOWORD(wparam) == MENU_PANTALLAPRINCIPAL && HIWORD(wparam) == BN_CLICKED) {
			HWND hPrincipal = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_PRINCIPAL), NULL, fPrincipal);
			ShowWindow(hPrincipal, SW_SHOW);
			DestroyWindow(hwnd);
		}
		else if (LOWORD(wparam) == MENU_VACUNAS_REGISTRO && HIWORD(wparam) == BN_CLICKED) {
			HWND hRegistroVaccine = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_RE_VACUNA), NULL, fRegisterVaccine);
			ShowWindow(hRegistroVaccine, SW_SHOW);
			DestroyWindow(hwnd);
		}
		else if (LOWORD(wparam) == MENU_VACUNAS_BAJA && HIWORD(wparam) == BN_CLICKED) {
			HWND hDeleteVaccine = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_DELETE_VACUNA), NULL, fDeleteVaccine);
			ShowWindow(hDeleteVaccine, SW_SHOW);
			DestroyWindow(hwnd);
		}
		else if (LOWORD(wparam) == MENU_VACUNAS_CAMBIO && HIWORD(wparam) == BN_CLICKED) {
			HWND hChangeVaccine = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_CHANGE_VACCINE), NULL, fChangeVaccine);
			ShowWindow(hChangeVaccine, SW_SHOW);
			DestroyWindow(hwnd);
		}
		else if (LOWORD(wparam) == MENU_PERSONAS_BAJA && HIWORD(wparam) == BN_CLICKED) {
			HWND hDeletePersonas = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_BAJA_PERSONAS), NULL, fDeletePerson);
			ShowWindow(hDeletePersonas, SW_SHOW);
			DestroyWindow(hwnd);
		}
		else if (LOWORD(wparam) == MENU_PERSONAS_CAMBIO && HIWORD(wparam) == BN_CLICKED) {
			HWND hChangePersonas = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_CHANGE_PERSON), NULL, fChangePerson);
			ShowWindow(hChangePersonas, SW_SHOW);
			DestroyWindow(hwnd);
		}
		else if (LOWORD(wparam) == MENU_CARNE_RE && HIWORD(wparam) == BN_CLICKED) {
			HWND hRegisterCarnet = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_REG_CARNET), NULL, fRegisterCarnet);
			ShowWindow(hRegisterCarnet, SW_SHOW);
			DestroyWindow(hwnd);
		}
		else if (LOWORD(wparam) == MENU_CARNE_BAJA && HIWORD(wparam) == BN_CLICKED) {
			HWND hDeleteCarnet = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_DELETE_CARNET), NULL, fDeleteCarnet);
			ShowWindow(hDeleteCarnet, SW_SHOW);
			DestroyWindow(hwnd);
		}
		else if (LOWORD(wparam) == MENU_CARNE_CAMBIO && HIWORD(wparam) == BN_CLICKED) {
			HWND hChangeCarnet = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_CHANGE_CARNET), NULL, fChangeCarnet);
			ShowWindow(hChangeCarnet, SW_SHOW);
			DestroyWindow(hwnd);
		}
		else if (LOWORD(wparam) == BTN_MENU_REPORT_NAME && HIWORD(wparam) == BN_CLICKED) {
			HWND hQuickSort = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_REPORTE_QUICKSORT), NULL, fReportQuickSort);
			ShowWindow(hQuickSort, SW_SHOW);
			DestroyWindow(hwnd);
		}
		else if (LOWORD(wparam) == BTN_OK_HEAPSORT && HIWORD(wparam) == BN_CLICKED) {
			reportHeapSortTxt(globalIdHeapSort++);
			MessageBox(NULL, "Reporte HeapSort generado!", "YEIH", MB_ICONINFORMATION);
			saveMaxIdHeapSort();
		}
	}break;
	case WM_CLOSE: {
		HWND hLogin = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_LOGIN_USER), NULL, fLogin);
		ShowWindow(hLogin, SW_SHOW);
		DestroyWindow(hwnd);
	}
				 break;
	case WM_DESTROY:
		break;
	}
	return FALSE;
}

BOOL CALLBACK fReportQuickSort(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
	switch (msg) {
	case WM_INITDIALOG: {
		int cant = 0;
		string infoQuick[259];
		reportQuickSort(cant, infoQuick, hwnd, LB_QUICKSORT_REPORT);
	}break;
	case WM_COMMAND: {
		if (LOWORD(wparam) == MENU_PERSONAS_REGISTRO && HIWORD(wparam) == BN_CLICKED) {
			HWND hRegisterPerson = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_REG_PERSON), NULL, fRegisterPerson);
			ShowWindow(hRegisterPerson, SW_SHOW);
			DestroyWindow(hwnd);
		}
		else if (LOWORD(wparam) == MENU_PANTALLAPRINCIPAL && HIWORD(wparam) == BN_CLICKED) {
			HWND hPrincipal = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_PRINCIPAL), NULL, fPrincipal);
			ShowWindow(hPrincipal, SW_SHOW);
			DestroyWindow(hwnd);
		}
		else if (LOWORD(wparam) == MENU_VACUNAS_REGISTRO && HIWORD(wparam) == BN_CLICKED) {
			HWND hRegistroVaccine = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_RE_VACUNA), NULL, fRegisterVaccine);
			ShowWindow(hRegistroVaccine, SW_SHOW);
			DestroyWindow(hwnd);
		}
		else if (LOWORD(wparam) == MENU_VACUNAS_BAJA && HIWORD(wparam) == BN_CLICKED) {
			HWND hDeleteVaccine = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_DELETE_VACUNA), NULL, fDeleteVaccine);
			ShowWindow(hDeleteVaccine, SW_SHOW);
			DestroyWindow(hwnd);
		}
		else if (LOWORD(wparam) == MENU_VACUNAS_CAMBIO && HIWORD(wparam) == BN_CLICKED) {
			HWND hChangeVaccine = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_CHANGE_VACCINE), NULL, fChangeVaccine);
			ShowWindow(hChangeVaccine, SW_SHOW);
			DestroyWindow(hwnd);
		}
		else if (LOWORD(wparam) == MENU_PERSONAS_BAJA && HIWORD(wparam) == BN_CLICKED) {
			HWND hDeletePersonas = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_BAJA_PERSONAS), NULL, fDeletePerson);
			ShowWindow(hDeletePersonas, SW_SHOW);
			DestroyWindow(hwnd);
		}
		else if (LOWORD(wparam) == MENU_PERSONAS_CAMBIO && HIWORD(wparam) == BN_CLICKED) {
			HWND hChangePersonas = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_CHANGE_PERSON), NULL, fChangePerson);
			ShowWindow(hChangePersonas, SW_SHOW);
			DestroyWindow(hwnd);
		}
		else if (LOWORD(wparam) == MENU_CARNE_RE && HIWORD(wparam) == BN_CLICKED) {
			HWND hRegisterCarnet = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_REG_CARNET), NULL, fRegisterCarnet);
			ShowWindow(hRegisterCarnet, SW_SHOW);
			DestroyWindow(hwnd);
		}
		else if (LOWORD(wparam) == MENU_CARNE_BAJA && HIWORD(wparam) == BN_CLICKED) {
			HWND hDeleteCarnet = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_DELETE_CARNET), NULL, fDeleteCarnet);
			ShowWindow(hDeleteCarnet, SW_SHOW);
			DestroyWindow(hwnd);
		}
		else if (LOWORD(wparam) == MENU_CARNE_CAMBIO && HIWORD(wparam) == BN_CLICKED) {
			HWND hChangeCarnet = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_CHANGE_CARNET), NULL, fChangeCarnet);
			ShowWindow(hChangeCarnet, SW_SHOW);
			DestroyWindow(hwnd);
		}
		else if (LOWORD(wparam) == BTN_MENU_REPORT_ID && HIWORD(wparam) == BN_CLICKED) {
			HWND hHeapSort = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_REPORTE_HEAPSORT), NULL, fReportHeapSort);
			ShowWindow(hHeapSort, SW_SHOW);
			DestroyWindow(hwnd);
		}
		else if (LOWORD(wparam) == BTN_OK_QUICKSORT && HIWORD(wparam) == BN_CLICKED) {
			reportQuickSortTxt(globalIdQuickSort++);
			MessageBox(NULL, "Reporte QuickSort generado!", "YEIH", MB_ICONINFORMATION);
			saveMaxIdQuickSort();
		}
	}break;
	case WM_CLOSE: {
		HWND hLogin = CreateDialog(hGlobalInst, MAKEINTRESOURCE(DLG_LOGIN_USER), NULL, fLogin);
		ShowWindow(hLogin, SW_SHOW);
		DestroyWindow(hwnd);
	}
				 break;
	case WM_DESTROY:
		break;
	}
	return FALSE;
}
#pragma endregion

#pragma region FUNCIONES_CUERPO
void clearHwnd(HWND hwnd, int id) {
	HWND hEditBox = GetDlgItem(hwnd, id);
	SetWindowText(hEditBox, "");
}

bool findUser(string clave) {
	uAux = uOrigin;
	bool find = true;
	while (uAux->clave.compare(clave) != 0) {
		if (uAux->nextU == NULL) {
			uAux = uOrigin;
			return false;
		}
		uAux = uAux->nextU;
	}
	uAux = uOrigin;
	return true;
}

bool findCarnet(string curp) {
	cAux = cOrigin;
	bool find = true;
	const char* curpTemp = curp.c_str();
	while (strcmp(cAux->curpCarnet, curpTemp) != 0) {
		if (cAux->nextC == NULL) {
			cAux = cOrigin;
			return false;
		}
		cAux = cAux->nextC;

	}
	cAux = cOrigin;
	return true;
}

bool searchVaccineCopy(string clave) {
	vAux = vOrigin;
	bool find = true;
	while (vAux->claveVaccine.compare(clave) != 0) {
		if (vAux->nextV == NULL) {
			vAux = vOrigin;
			return false;
		}
		vAux = vAux->nextV;
	}
	vAux = vOrigin;
	return true;
}

bool searchVaccineCopy2(string clave, Vaccine* vAux) {
	vAux = vOrigin;
	bool find = true;
	while (vAux->claveVaccine.compare(clave) != 0) {
		if (vAux->nextV == NULL) {
			vAux = vOrigin;
			return false;
		}
		vAux = vAux->nextV;
	}
	vAux = vOrigin;
	return true;
}

bool findUser(string clave, string pass) {
	uAux = uOrigin;
	bool find = true;
	while (uAux->clave.compare(clave) != 0) {
		if (uAux->nextU == NULL) {
			uAux = uOrigin;
			return false;
		}
		uAux = uAux->nextU;
	}
	if (uAux->password.compare(pass) != 0) {
		uAux = uOrigin;
		return false;
	}
	uLogged.idUser = uAux->idUser;
	uLogged.nameUser = uAux->nameUser;
	uAux = uOrigin;
	return true;
}

bool saveUser(string name, string pass, string amU, string apU, string clav, int id) {
	if (uOrigin == NULL) {
		uOrigin = new User;
		uOrigin->nextU = NULL;
		uOrigin->prevU = NULL;
		uOrigin->nameUser = name;
		uOrigin->password = pass;
		uOrigin->amUser = amU;
		uOrigin->apUser = apU;
		uOrigin->clave = clav;
		uOrigin->idUser = id;
	}
	else {
		if (findUser(name)) {
			return false;
		}
		while (uAux->nextU != NULL)
			uAux = uAux->nextU;
		uAux->nextU = new User;
		uAux->nextU->prevU = uAux;
		uAux = uAux->nextU;
		uAux->nextU = NULL;
		uAux->nameUser = name;
		uAux->password = pass;
		uAux->amUser = amU;
		uAux->apUser = apU;
		uAux->clave = clav;
		uAux->idUser = id;
	}
	uAux = uOrigin;
	return true;
}

bool saveVaccine(string tipo, string marca, string dosis, string clave, string des, float precio, int id) {
	if (vOrigin == NULL) {
		vOrigin = new Vaccine;
		vOrigin->nextV = NULL;
		vOrigin->prevV = NULL;
		vOrigin->tipo = tipo;
		vOrigin->marca = marca;
		vOrigin->dosis = dosis;
		vOrigin->claveVaccine = clave;
		strcpy_s(vOrigin->description, des.c_str());
		vOrigin->precio = precio;
		vOrigin->idVaccine = id;
	}
	else {
		if (searchVaccineCopy(clave)) {
			return false;
		}
		while (vAux->nextV != NULL)
			vAux = vAux->nextV;
		vAux->nextV = new Vaccine;
		vAux->nextV->prevV = vAux;
		vAux = vAux->nextV;
		vAux->nextV = NULL;
		vAux->tipo = tipo;
		vAux->marca = marca;
		vAux->dosis = dosis;
		vAux->claveVaccine = clave;
		strcpy_s(vAux->description, des.c_str());
		vAux->precio = precio;
		vAux->idVaccine = id;
	}
	vAux = vOrigin;
	return true;
}

bool savePerson(string ap, string am, string name, string curp, string rfc, string fecha, string calle, string colonia, string estado, string civil, string tele, string sexo, string grupo, string perfil, string ciudad, string identiti, int id) {
	if (pOrigin == NULL) {
		pOrigin = new Person;
		pOrigin->nextP = NULL;
		pOrigin->prevP = NULL;
		pOrigin->apPerson = ap;
		pOrigin->amPerson = am;
		pOrigin->namePerson = name;
		pOrigin->RFC = rfc;
		pOrigin->fechaNaci = fecha;
		pOrigin->calle = calle;
		pOrigin->colonia = colonia;
		pOrigin->estado = estado;
		pOrigin->estadoCivil = civil;
		pOrigin->telefono = tele;
		pOrigin->sexo = sexo;
		pOrigin->grupoOcup = grupo;
		pOrigin->perfilRies = perfil;
		pOrigin->ciudad = ciudad;
		pOrigin->idPerson = id;
		strcpy_s(pOrigin->CURP, curp.c_str());
		strcpy_s(pOrigin->identificacion, pImageTempPerson.c_str());
		pOrigin->identiString = identiti;
	}
	else {
		if (searchPersonCopy(rfc))
			return false;
		if (searchPersonCopy2(curp))
			return false;

		while (pAux->nextP != NULL)
			pAux = pAux->nextP;
		pAux->nextP = new Person;
		pAux->nextP->prevP = pAux;
		pAux = pAux->nextP;
		pAux->nextP = NULL;
		pAux->apPerson = ap;
		pAux->amPerson = am;
		pAux->namePerson = name;
		pAux->RFC = rfc;
		pAux->fechaNaci = fecha;
		pAux->calle = calle;
		pAux->colonia = colonia;
		pAux->estado = estado;
		pAux->estadoCivil = civil;
		pAux->telefono = tele;
		pAux->sexo = sexo;
		pAux->grupoOcup = grupo;
		pAux->perfilRies = perfil;
		pAux->ciudad = ciudad;
		pAux->idPerson = id;
		strcpy_s(pAux->CURP, curp.c_str());
		strcpy_s(pAux->identificacion, pImageTempPerson.c_str());
		pAux->identiString = identiti;
	}
	pAux = pOrigin;
	return true;
}

bool saveCarnet(string curpCar, string vacuCar, string dosisCar, string fechaCar, string fechaCar2, string loteCar, string centroVacu ,string ap, string am, string name, string rfc, string fechaNaci, string calle, string colonia, string estado, string civil, string telefono, string ciudad, string sexo, string grupo, string perfil, string identiti, string clave, string des, float precio, int id) {
	if (cOrigin == NULL) {
		cOrigin = new Carnet;
		cOrigin->nextC = NULL;
		cOrigin->prevC = NULL;
		strcpy_s(cOrigin->curpCarnet, curpCar.c_str());
		cOrigin->vacunaCarnet = vacuCar;
		cOrigin->dosisCarnet = dosisCar;
		cOrigin->fechaDosisCarnet = fechaCar;
		cOrigin->fechaDosisCarnet2 = fechaCar2;
		cOrigin->loteMarca = loteCar;
		cOrigin->centroDeVacu = centroVacu;
		cOrigin->amPersonCar = am;
		cOrigin->apPersonCar = ap;
		cOrigin->namePersonCar = name;
		cOrigin->RFCCar = rfc;
		cOrigin->fechaNaciCar = fechaNaci;
		cOrigin->calleCar = calle;
		cOrigin->coloniaCar = colonia;
		cOrigin->estadoCar = estado;
		cOrigin->estadoCivilCar = civil;
		cOrigin->telefonoCar = telefono;
		cOrigin->ciudadCar = ciudad;
		cOrigin->sexoCar = sexo;
		cOrigin->grupoOcupCar = grupo;
		cOrigin->perfilRiesCar = perfil;
		cOrigin->identiStringCar = identiti;
		cOrigin->claveVaccineCar = clave;
		cOrigin->precioCar = precio;
		strcpy_s(cOrigin->descriptionCar, des.c_str());
		strcpy_s(cOrigin->identificacionCar, pImageTempPerson.c_str());
		cOrigin->idCarnet = id;
	}
	else {
		if (findCarnet(curpCar)) {
			return false;
		}
		while (cAux->nextC != NULL)
			cAux = cAux->nextC;
		cAux->nextC = new Carnet;
		cAux->nextC->prevC = cAux;
		cAux = cAux->nextC;
		cAux->nextC = NULL;
		strcpy_s(cAux->curpCarnet, curpCar.c_str());
		cAux->vacunaCarnet = vacuCar;
		cAux->dosisCarnet = dosisCar;
		cAux->fechaDosisCarnet = fechaCar;
		cAux->fechaDosisCarnet2 = fechaCar2;
		cAux->loteMarca = loteCar;
		cAux->centroDeVacu = centroVacu;
		cAux->amPersonCar = am;
		cAux->apPersonCar = ap;
		cAux->namePersonCar = name;
		cAux->RFCCar = rfc;
		cAux->fechaNaciCar = fechaNaci;
		cAux->calleCar = calle;
		cAux->coloniaCar = colonia;
		cAux->estadoCar = estado;
		cAux->estadoCivilCar = civil;
		cAux->telefonoCar = telefono;
		cAux->ciudadCar = ciudad;
		cAux->sexoCar = sexo;
		cAux->grupoOcupCar = grupo;
		cAux->perfilRiesCar = perfil;
		cAux->identiStringCar = identiti;
		cAux->claveVaccineCar = clave;
		cAux->precioCar = precio;
		strcpy_s(cAux->descriptionCar, des.c_str());
		strcpy_s(cAux->identificacionCar, pImageTempPerson.c_str());
		cAux->idCarnet = id;
	}
	cAux = cOrigin;
	return true;
}

bool searchPersonCopy(string rfc) {
	pAux = pOrigin;
	bool find = true;
	while (pAux->RFC.compare(rfc) != 0) {
		if (pAux->nextP == NULL) {
			pAux = pOrigin;
			return false;
		}
		pAux = pAux->nextP;

	}
	pAux = pOrigin;
	return true;
}

bool searchPersonCopy2(string curp) {
	pAux = pOrigin;
	bool find = true;
	const char *curpTemp = curp.c_str();
	while (strcmp(pAux->CURP, curpTemp) != 0) {
		if (pAux->nextP == NULL) {
			pAux = pOrigin;
			return false;
		}
		pAux = pAux->nextP;

	}
	pAux = pOrigin;
	return true;
}

string getHwndText(HWND hwnd, int ID) {
	HWND hEditBox = GetDlgItem(hwnd, ID);
	int textLength = GetWindowTextLength(hEditBox);
	if (textLength < 1) {
		return "-1";
	}
	char text[100];
	GetWindowText(hEditBox, text, ++textLength);
	string realText(text);
	return realText;
}

void saveToFilePerson() {
	fileManager.open("person.bin", ios::binary | ios::out | ios::trunc);
	if (fileManager.is_open()) {
		while (pAux != NULL) {
			fileManager.write(reinterpret_cast<char*>(pAux), sizeof(Person));
			pAux = pAux->nextP;
		}
		fileManager.close();
	}
	else {
		MessageBox(NULL, "No se pudo abrir el archivo de personas", "Aviso", MB_ICONWARNING);
	}
	pAux = pOrigin;
}

void saveToFileUser() {
	fileManager.open("users.txt", ios::out | ios::trunc);
	if (fileManager.is_open()) {
		while (uAux != NULL) {
			fileManager.write(reinterpret_cast<char*>(uAux), sizeof(User));
			uAux = uAux->nextU;
		}
		fileManager.close();
	}
	else {
		MessageBox(NULL, "No se pudo abrir el archivo de usuarios", "Aviso", MB_ICONWARNING);
	}
	uAux = uOrigin;
}

void saveToFileVaccine() {
	fileManager.open("vaccine.bin", ios::binary | ios::out | ios::trunc);
	if (fileManager.is_open()) {
		while (vAux != NULL) {
			fileManager.write(reinterpret_cast<char*>(vAux), sizeof(Vaccine));
			vAux = vAux->nextV;
		}
		fileManager.close();
	}
	else {
		MessageBox(NULL, "No se pudo abrir el archivo de vacunas", "Aviso", MB_ICONWARNING);
	}
	vAux = vOrigin;
}

void saveToFileCarnet() {
	fileManager.open("carnet.bin", ios::binary | ios::out | ios::trunc);
	if (fileManager.is_open()) {
		while (cAux != NULL) {
			fileManager.write(reinterpret_cast<char*>(cAux), sizeof(Carnet));
			cAux = cAux->nextC;
		}
		fileManager.close();
	}
	else {
		MessageBox(NULL, "No se pudo abrir el archivo de carnets", "Aviso", MB_ICONWARNING);
	}
	cAux = cOrigin;
}

void loadToFileUser() {
	fileManager.open("users.txt", ios::in | ios::ate);
	if (fileManager.is_open()) {
		int fileSize = fileManager.tellg();
		if (fileSize < 1) {
			MessageBox(NULL, "Archivo vacio de usuarios", "Aviso", MB_ICONWARNING);
			fileManager.close();
			return;
		}
		for (int i = 0; i < (fileSize/sizeof(User)); i++) {
			fileManager.seekg(i * sizeof(User));
			if (uOrigin == NULL) {
				User* temp = new User;
				uOrigin = new User;
				uOrigin->nextU = NULL;
				uOrigin->prevU = NULL;
				fileManager.read(reinterpret_cast<char*>(temp), sizeof(User));
				uOrigin->nameUser = temp->nameUser;
				uOrigin->password = temp->password;
				uOrigin->amUser = temp->amUser;
				uOrigin->apUser = temp->apUser;
				uOrigin->clave = temp->clave;
				uOrigin->idUser = temp->idUser;
				delete reinterpret_cast<char*>(temp);
			}
			else {
				while (uAux->nextU != NULL)
					uAux = uAux->nextU;
				User* temp = new User;
				uAux->nextU = new User;
				uAux->nextU->prevU = uAux;
				uAux = uAux->nextU;
				uAux->nextU = NULL;
				fileManager.read(reinterpret_cast<char*>(temp), sizeof(User));
				uAux->nameUser = temp->nameUser;
				uAux->password = temp->password;
				uAux->amUser = temp->amUser;
				uAux->apUser = temp->apUser;
				uAux->clave = temp->clave;
				uAux->idUser = temp->idUser;
				delete reinterpret_cast<char*>(temp);
			}
			uAux = uOrigin;
		}
		fileManager.close();
	}
	else {
		MessageBox(NULL, "No se pudo abrir el archivo de usuarios", "Aviso", MB_ICONWARNING);
	}
}

void loadToFilePerson() {
	fileManager.open("person.bin", ios::binary | ios::in | ios::ate);
	if (fileManager.is_open()) {
		int fileSize = fileManager.tellg();
		if (fileSize < 1) {
			//MessageBox(NULL, "Arhivo vacio de personas", "Aviso", MB_ICONWARNING);
			fileManager.close();
			return;
		}
		for (int i = 0; i < fileSize / sizeof(Person); i++) {
			fileManager.seekg(i * sizeof(Person));
			if (pOrigin == NULL) {
				Person* temp = new Person;
				pOrigin = new Person;
				pOrigin->nextP = NULL;
				pOrigin->prevP = NULL;
				fileManager.read(reinterpret_cast<char*>(temp), sizeof(Person));
				pOrigin->amPerson = temp->amPerson;
				pOrigin->apPerson = temp->apPerson;
				pOrigin->calle = temp->calle;
				pOrigin->colonia = temp->colonia;
				pOrigin->ciudad = temp->ciudad;
				pOrigin->estado = temp->estado;
				pOrigin->estadoCivil = temp->estadoCivil;
				pOrigin->fechaNaci = temp->fechaNaci;
				pOrigin->grupoOcup = temp->grupoOcup;
				pOrigin->idPerson = temp->idPerson;
				pOrigin->namePerson = temp->namePerson;
				pOrigin->perfilRies = temp->perfilRies;
				pOrigin->RFC = temp->RFC;
				pOrigin->sexo = temp->sexo;
				pOrigin->telefono = temp->telefono;
				strcpy_s(pOrigin->identificacion, temp->identificacion);
				strcpy_s(pOrigin->CURP, temp->CURP);
				pOrigin->identiString = temp->identiString;
				delete reinterpret_cast<char*>(temp);
			}
			else {
				while (pAux->nextP != NULL)
					pAux = pAux->nextP;
				Person* temp = new Person;
				pAux->nextP = new Person;
				pAux->nextP->prevP = pAux;
				pAux = pAux->nextP;
				pAux->nextP = NULL;
				fileManager.read(reinterpret_cast<char*>(temp), sizeof(Person));
				pAux->amPerson = temp->amPerson;
				pAux->apPerson = temp->apPerson;
				pAux->calle = temp->calle;
				pAux->colonia = temp->colonia;
				pAux->ciudad = temp->ciudad;
				pAux->estado = temp->estado;
				pAux->estadoCivil = temp->estadoCivil;
				pAux->fechaNaci = temp->fechaNaci;
				pAux->grupoOcup = temp->grupoOcup;
				pAux->idPerson = temp->idPerson;
				pAux->namePerson = temp->namePerson;
				pAux->perfilRies = temp->perfilRies;
				pAux->RFC = temp->RFC;
				pAux->sexo = temp->sexo;
				pAux->telefono = temp->telefono;
				strcpy_s(pAux->identificacion, temp->identificacion);
				strcpy_s(pAux->CURP, temp->CURP);
				pAux->identiString = temp->identiString;
				delete reinterpret_cast<char*>(temp);
			}
			pAux = pOrigin;
		}
		fileManager.close();
	}
	else {
		//MessageBox(NULL, "No se pudo abrir el archivo", "Aviso", MB_ICONWARNING);
	}
}

void loadToFileVaccine() {
	fileManager.open("vaccine.bin", ios::binary | ios::in | ios::ate);
	if (fileManager.is_open()) {
		int fileSize = fileManager.tellg();
		if (fileSize < 1) {
			//MessageBox(NULL, "Arhivo vacio de vacunas", "Aviso", MB_ICONWARNING);
			fileManager.close();
			return;
		}
		for (int i = 0; i < fileSize / sizeof(Vaccine); i++) {
			fileManager.seekg(i * sizeof(Vaccine));
			if (vOrigin == NULL) {
				Vaccine* temp = new Vaccine;
				vOrigin = new Vaccine;
				vOrigin->nextV = NULL;
				vOrigin->prevV = NULL;
				fileManager.read(reinterpret_cast<char*>(temp), sizeof(Vaccine));
				vOrigin->claveVaccine = temp->claveVaccine;
				vOrigin->dosis = temp->dosis;
				vOrigin->marca = temp->marca;
				vOrigin->precio = temp->precio;
				vOrigin->tipo = temp->tipo;
				strcpy_s(vOrigin->description, temp->description);
				vOrigin->idVaccine = temp->idVaccine;
				delete reinterpret_cast<char*>(temp);
			}
			else {
				while (vAux->nextV != NULL)
					vAux = vAux->nextV;
				Vaccine* temp = new Vaccine;
				vAux->nextV = new Vaccine;
				vAux->nextV->prevV = vAux;
				vAux = vAux->nextV;
				vAux->nextV = NULL;
				fileManager.read(reinterpret_cast<char*>(temp), sizeof(Vaccine));
				vAux->claveVaccine = temp->claveVaccine;
				vAux->dosis = temp->dosis;
				vAux->marca = temp->marca;
				vAux->precio = temp->precio;
				vAux->tipo = temp->tipo;
				strcpy_s(vAux->description, temp->description);
				vAux->idVaccine = temp->idVaccine;
				delete reinterpret_cast<char*>(temp);
			}
			vAux = vOrigin;
		}
		fileManager.close();
	}
	else {
		//MessageBox(NULL, "No se pudo abrir el archivo", "Aviso", MB_ICONWARNING);
	}
}

void loadToFileCarnet() {
	fileManager.open("carnet.bin", ios::binary | ios::in | ios::ate);
	if (fileManager.is_open()) {
		int fileSize = fileManager.tellg();
		if (fileSize < 1) {
			//MessageBox(NULL, "Arhivo vacio de carnets", "Aviso", MB_ICONWARNING);
			fileManager.close();
			return;
		}
		for (int i = 0; i < fileSize / sizeof(Carnet); i++) {
			fileManager.seekg(i * sizeof(Carnet));
			if (cOrigin == NULL) {
				Carnet* temp = new Carnet;
				cOrigin = new Carnet;
				cOrigin->nextC = NULL;
				cOrigin->prevC = NULL;
				fileManager.read(reinterpret_cast<char*>(temp), sizeof(Carnet));
				strcpy_s(cOrigin->curpCarnet, temp->curpCarnet);
				cOrigin->vacunaCarnet = temp->vacunaCarnet;
				cOrigin->dosisCarnet = temp->dosisCarnet;
				cOrigin->fechaDosisCarnet = temp->fechaDosisCarnet;
				cOrigin->fechaDosisCarnet2 = temp->fechaDosisCarnet2;
				cOrigin->loteMarca = temp->loteMarca;
				cOrigin->centroDeVacu = temp->centroDeVacu;
				cOrigin->amPersonCar = temp->amPersonCar;
				cOrigin->apPersonCar = temp->apPersonCar;
				cOrigin->namePersonCar = temp->namePersonCar;
				cOrigin->RFCCar = temp->RFCCar;
				cOrigin->fechaNaciCar = temp->fechaNaciCar;
				cOrigin->calleCar = temp->calleCar;
				cOrigin->coloniaCar = temp->coloniaCar;
				cOrigin->estadoCar = temp->estadoCar;
				cOrigin->estadoCivilCar = temp->estadoCivilCar;
				cOrigin->telefonoCar = temp->telefonoCar;
				cOrigin->ciudadCar = temp->ciudadCar;
				cOrigin->sexoCar = temp->sexoCar;
				cOrigin->grupoOcupCar = temp->grupoOcupCar;
				cOrigin->perfilRiesCar = temp->perfilRiesCar;
				cOrigin->identiStringCar = temp->identiStringCar;
				cOrigin->claveVaccineCar = temp->claveVaccineCar;
				cOrigin->precioCar = temp->precioCar;
				strcpy_s(cOrigin->identificacionCar, temp->identificacionCar);
				strcpy_s(cOrigin->descriptionCar, temp->descriptionCar);
				cOrigin->idCarnet = temp->idCarnet;
				delete reinterpret_cast<char*>(temp);
			}
			else {
				while (cAux->nextC != NULL)
					cAux = cAux->nextC;
				Carnet* temp = new Carnet;
				cAux->nextC = new Carnet;
				cAux->nextC->prevC = cAux;
				cAux = cAux->nextC;
				cAux->nextC = NULL;
				fileManager.read(reinterpret_cast<char*>(temp), sizeof(Carnet));
				strcpy_s(cAux->curpCarnet, temp->curpCarnet);
				cAux->vacunaCarnet = temp->vacunaCarnet;
				cAux->dosisCarnet = temp->dosisCarnet;
				cAux->fechaDosisCarnet = temp->fechaDosisCarnet;
				cAux->fechaDosisCarnet2 = temp->fechaDosisCarnet2;
				cAux->loteMarca = temp->loteMarca;
				cAux->centroDeVacu = temp->centroDeVacu;
				cAux->amPersonCar = temp->amPersonCar;
				cAux->apPersonCar = temp->apPersonCar;
				cAux->namePersonCar = temp->namePersonCar;
				cAux->RFCCar = temp->RFCCar;
				cAux->fechaNaciCar = temp->fechaNaciCar;
				cAux->calleCar = temp->calleCar;
				cAux->coloniaCar = temp->coloniaCar;
				cAux->estadoCar = temp->estadoCar;
				cAux->estadoCivilCar = temp->estadoCivilCar;
				cAux->telefonoCar = temp->telefonoCar;
				cAux->ciudadCar = temp->ciudadCar;
				cAux->sexoCar = temp->sexoCar;
				cAux->grupoOcupCar = temp->grupoOcupCar;
				cAux->perfilRiesCar = temp->perfilRiesCar;
				cAux->identiStringCar = temp->identiStringCar;
				cAux->claveVaccineCar = temp->claveVaccineCar;
				cAux->precioCar = temp->precioCar;
				strcpy_s(cAux->identificacionCar, temp->identificacionCar);
				strcpy_s(cAux->descriptionCar, temp->descriptionCar);
				cAux->idCarnet = temp->idCarnet;
				delete reinterpret_cast<char*>(temp);
			}
			cAux = cOrigin;
		}
		fileManager.close();
	}
	else {
		//MessageBox(NULL, "No se pudo abrir el archivo", "Aviso", MB_ICONWARNING);
	}
}

void getMaxIdUser() {
	fileManager.open("userId.txt", ios::in);
	if (fileManager.is_open()) {
		fileManager >> globalId;
		fileManager.close();
	}
	else {
		//MessageBox(NULL, "No se pudo abrir el archivo de usuarios", "Aviso", MB_ICONWARNING);
	}
}

void getMaxIdPerson() {
	fileManager.open("personId.txt", ios::in);
	if (fileManager.is_open()) {
		fileManager >> globalIdPerson;
		fileManager.close();
	}
	else {
		//MessageBox(NULL, "No se pudo abrir el archivo de personas", "Aviso", MB_ICONWARNING);
	}
}

void getMaxIdVaccine() {
	fileManager.open("vaccineId.txt", ios::in);
	if (fileManager.is_open()) {
		fileManager >> globalIdVaccine;
		fileManager.close();
	}
	else {
		//MessageBox(NULL, "No se pudo abrir el archivo de vacunas", "Aviso", MB_ICONWARNING);
	}
}

void getMaxIdCarnet() {
	fileManager.open("carnetId.txt", ios::in);
	if (fileManager.is_open()) {
		fileManager >> globalIdCarnet;
		fileManager.close();
	}
	else {
		//MessageBox(NULL, "No se pudo abrir el archivo de carnet", "Aviso", MB_ICONWARNING);
	}
}

void saveMaxIdPerson() {
	fileManager.open("personId.txt", ios::out | ios::trunc);
	if (fileManager.is_open()) {
		fileManager << globalIdPerson;
		fileManager.close();
	}
	else {
		MessageBox(NULL, "No se pudo abrir el archivo de personas", "Aviso", MB_ICONWARNING);
	}
}

void saveMaxIdUser() {
	fileManager.open("userId.txt", ios::out | ios::trunc);
	if (fileManager.is_open()) {
		fileManager << globalId;
		fileManager.close();
	}
	else {
		MessageBox(NULL, "No se pudo abrir el archivo de usuarios", "Aviso", MB_ICONWARNING);
	}
}

void saveMaxIdVaccine() {
	fileManager.open("vaccineId.txt", ios::out | ios::trunc);
	if (fileManager.is_open()) {
		fileManager << globalIdVaccine;
		fileManager.close();
	}
	else {
		MessageBox(NULL, "No se pudo abrir el archivo de vacunas", "Aviso", MB_ICONWARNING);
	}
}

void saveMaxIdCarnet() {
	fileManager.open("carnetId.txt", ios::out | ios::trunc);
	if (fileManager.is_open()) {
		fileManager << globalIdCarnet;
		fileManager.close();
	}
	else {
		MessageBox(NULL, "No se pudo abrir el archivo de carnets", "Aviso", MB_ICONWARNING);
	}
}

void clearUser() {
	while (uAux != NULL) {
		User* temp = uAux;
		uAux = uAux->nextU;
		delete temp;
	}
	uAux = uOrigin = NULL;
}

void clearPerson() {
	while (pAux != NULL) {
		Person* temp = pAux;
		pAux = pAux->nextP;
		delete temp;
	}
	pAux = pOrigin = NULL;
}

void clearVaccine() {
	while (vAux != NULL) {
		Vaccine* temp = vAux;
		vAux = vAux->nextV;
		delete temp;
	}
	vAux = vOrigin = NULL;
}

void clearCarnet() {
	while (cAux != NULL) {
		Carnet* temp = cAux;
		cAux = cAux->nextC;
		delete temp;
	}
	cAux = cOrigin = NULL;
}

bool imprVaccine(HWND hwnd, int idLb) {
	HWND lb = GetDlgItem(hwnd, idLb);
	bool list = true;
	vAux = vOrigin;
	while (vAux != NULL) {

		SendMessage(lb, LB_ADDSTRING, NULL, (LPARAM)vAux->claveVaccine.c_str());
		vAux = vAux->nextV;
	}
	if (list) {
		return false;
	}
	vAux = vOrigin;
	return true;
}

Vaccine* searchVacineLB(string clave) {
	bool searchFound = true;
	vAux = vOrigin;
	while (clave.compare(vAux->claveVaccine) != 0) {
		if (vAux->nextV == NULL) {
			searchFound = false;
			break;
		}
		vAux = vAux->nextV;
	}
	if (searchFound == false) {
		return NULL;
	}
	return vAux;
}

void showVariablesVaccineDelete(HWND hwnd) {
	HWND lb = GetDlgItem(hwnd, LB_VACUNA_DELETE);
	int contador = SendMessage(lb, LB_GETCOUNT, 0, 0);
	int selec = -1;
	for (int i = 0; i < contador; i++) {
		if (SendMessage(lb, LB_GETSEL, i, 0) > 0) {
			selec = i;
			break;
		}
	}
	char tempV[40];
	SendMessage(lb, LB_GETTEXT, selec, (LPARAM)tempV);
	string textVaccine(tempV);
	Vaccine* vaccineFounded = searchVacineLB(textVaccine);
	HWND htipo = GetDlgItem(hwnd, TXT_TIPO_VACUNADELETE);
	HWND hmarca = GetDlgItem(hwnd, TXT_MARCA_VACUNADELETE);
	HWND hdosis = GetDlgItem(hwnd, TXT_DOSIS_VACUNADELETE);
	HWND hclave = GetDlgItem(hwnd, TXT_CLAVE_VACUNADELETE);
	HWND hdescripcion = GetDlgItem(hwnd, TXT_DES_VACUNADELETE);
	HWND hprecio = GetDlgItem(hwnd, TXT_PRECIO_VACUNADELETE);
	char tipoC[20], marcaC[20], dosisC[20], claveC[20], descripC[40], precioC[10];
	string tempTipo = vaccineFounded->tipo;
	string tempMarca = vaccineFounded->marca;
	string tempDosis = vaccineFounded->dosis;
	string tempClave = vaccineFounded->claveVaccine;
	string tempDes = vaccineFounded->description;
	float tempPrecio = vaccineFounded->precio;
	strcpy_s(tipoC, tempTipo.c_str());
	SetWindowText(htipo, tipoC);
	strcpy_s(marcaC, tempMarca.c_str());
	SetWindowText(hmarca, marcaC);
	strcpy_s(dosisC, tempDosis.c_str());
	SetWindowText(hdosis, dosisC);
	strcpy_s(claveC, tempClave.c_str());
	SetWindowText(hclave, claveC);
	strcpy_s(descripC, tempDes.c_str());
	SetWindowText(hdescripcion, descripC);
	_itoa_s(tempPrecio, precioC, 10);
	SetWindowText(hprecio, precioC);
}

void showVariablesVaccineChange(HWND hwnd) {
	HWND lb = GetDlgItem(hwnd, LB_VACUNA_CHANGE);
	int contador = SendMessage(lb, LB_GETCOUNT, 0, 0);
	int selec = -1;
	for (int i = 0; i < contador; i++) {
		if (SendMessage(lb, LB_GETSEL, i, 0) > 0) {
			selec = i;
			break;
		}
	}
	char tempV[40];
	SendMessage(lb, LB_GETTEXT, selec, (LPARAM)tempV);
	string textVaccine(tempV);
	Vaccine* vaccineFounded = searchVacineLB(textVaccine);
	HWND htipo = GetDlgItem(hwnd, TXT_TIPO_VACUNACHANGE);
	HWND hmarca = GetDlgItem(hwnd, TXT_MARCA_VACUNACHANGE);
	HWND hdosis = GetDlgItem(hwnd, TXT_DOSIS_VACUNACHANGE);
	HWND hclave = GetDlgItem(hwnd, TXT_CLAVE_VACUNACHANGE);
	HWND hdescripcion = GetDlgItem(hwnd, TXT_DES_VACUNACHANGE);
	HWND hprecio = GetDlgItem(hwnd, TXT_PRECIO_VACUNACHANGE);
	char tipoC[20], marcaC[20], dosisC[20], claveC[20], descripC[40], precioC[10];
	string tempTipo = vaccineFounded->tipo;
	string tempMarca = vaccineFounded->marca;
	string tempDosis = vaccineFounded->dosis;
	string tempClave = vaccineFounded->claveVaccine;
	string tempDes = vaccineFounded->description;
	float tempPrecio = vaccineFounded->precio;
	strcpy_s(tipoC, tempTipo.c_str());
	SetWindowText(htipo, tipoC);
	strcpy_s(marcaC, tempMarca.c_str());
	SetWindowText(hmarca, marcaC);
	strcpy_s(dosisC, tempDosis.c_str());
	SetWindowText(hdosis, dosisC);
	strcpy_s(claveC, tempClave.c_str());
	SetWindowText(hclave, claveC);
	strcpy_s(descripC, tempDes.c_str());
	SetWindowText(hdescripcion, descripC);
	_itoa_s(tempPrecio, precioC, 10);
	SetWindowText(hprecio, precioC);
	idVaccineFounded = vAux->idVaccine;
}

Vaccine* searchVaccine(string clave, Vaccine* vAux) {
	bool searchFound = true;
	while (clave.compare(vAux->claveVaccine) != 0) {
		if (vAux->nextV == NULL) {
			searchFound = false;
			break;
		}
		vAux = vAux->nextV;
	}
	if (searchFound == false) {
		return NULL;
	}
	return vAux;
}

Vaccine* searchVaccineWithId(int id, Vaccine* vAux, string clave) {
	bool searchFound = true;
	while ((id != vAux->idVaccine) != 0) {

		if (vAux->nextV == NULL) {
			searchFound = false;
			break;
		}
		vAux = vAux->nextV;
	}
	if (searchFound == false) {
		return NULL;
	}
	return vAux;
}

void borrarVaccine() {
	if (vAux->nextV == NULL && vAux->prevV == NULL) {
		delete vAux;
		vAux = vOrigin = NULL;
	}
	else if (vAux->prevV == NULL) {
		vOrigin = vOrigin->nextV;
		vOrigin->prevV = NULL;
		delete vAux;
		vAux = vOrigin;
	}
	else if (vAux->nextV == NULL) {
		vAux->prevV->nextV = NULL;

		delete vAux;
		vAux = vOrigin;
	}
	else {

		vAux->prevV->nextV = vAux->nextV;

		vAux->nextV->prevV = vAux->prevV;

		delete vAux;
		vAux = vOrigin;
	}
}

bool imprPerson(HWND hwnd, int idLb) {
	HWND lb = GetDlgItem(hwnd, idLb);
	bool list = true;
	pAux = pOrigin;
	while (pAux != NULL) {

		SendMessage(lb, LB_ADDSTRING, NULL, (LPARAM)pAux->CURP);
		pAux = pAux->nextP;
	}
	if (list) {
		return false;
	}
	pAux = pOrigin;
	return true;
}

Vaccine* changeVaccine(Vaccine* vAux, string tipo, string marca, string dosis, string clave, string desc, float precio) {
	vAux->tipo = tipo;
	vAux->marca = marca;
	vAux->dosis = dosis;
	vAux->claveVaccine = clave;
	strcpy_s(vAux->description, desc.c_str());
	vAux->precio = precio;
	return vAux;
}

void showVariablesPersonDelete(HWND hwnd) {
	HWND lb = GetDlgItem(hwnd, LB_DELETE_PERSON);
	int contador = SendMessage(lb, LB_GETCOUNT, 0, 0);
	int selec = -1;
	for (int i = 0; i < contador; i++) {
		if (SendMessage(lb, LB_GETSEL, i, 0) > 0) {
			selec = i;
			break;
		}
	}
	char tempP[40];
	SendMessage(lb, LB_GETTEXT, selec, (LPARAM)tempP);
	string textPerson(tempP);
	Person* personFounded = searchPersonLB(textPerson);
	HWND hApPerson = GetDlgItem(hwnd, TXT_AP_PERSONDELETE);
	HWND hAmPerson = GetDlgItem(hwnd, TXT_AM_PERSONDELETE);
	HWND hName = GetDlgItem(hwnd, TXT_NAME_PERSONDELETE);
	HWND hCurp = GetDlgItem(hwnd, TXT_CURP_PERSONDELETE);
	HWND hRfc = GetDlgItem(hwnd, TXT_RFC_PERSONDELETE);
	HWND hFecha = GetDlgItem(hwnd, TXT_FECHA_PERSONDELETE);
	HWND hCalle = GetDlgItem(hwnd, TXT_CALLE_PERSONDELETE);
	HWND hColonia = GetDlgItem(hwnd, TXT_COLONIA_PERSONDELETE);
	HWND hCiudad = GetDlgItem(hwnd, TXT_CIUDAD_PERSONDELETE);
	HWND hEstado = GetDlgItem(hwnd, TXT_ESTADO_PERSONDELETE);
	HWND hCivil = GetDlgItem(hwnd, TXT_CIVIL_PERSONDELETE);
	HWND hTelefo = GetDlgItem(hwnd, TXT_TELEFO_PERSONDELETE);
	HWND hSexo = GetDlgItem(hwnd, TXT_SEXO_PERSONDELETE);
	HWND hGrupo = GetDlgItem(hwnd, TXT_GRUPO_PERSONDELETE);
	HWND hPerfil = GetDlgItem(hwnd, TXT_PERFIL_PERSONDELETE);
	HWND hIdentiti = GetDlgItem(hwnd, TXT_IDENTIDAD_PERSONDELETE);
	char ApPersonC[20], AmPersonC[20], NameC[20], CurpC[20], RfcC[20], FechaC[20], CalleC[20];
	char ColoniaC[20], CiudadC[20], EstadoC[20], CivilC[20], TelefoC[20], SexoC[20];
	char GrupoC[20], PerfilC[20], IdentitiC[10];
	string tempApPerson = personFounded->apPerson;
	string tempAmPerson = personFounded->amPerson;
	string tempName = personFounded->namePerson;
	string tempCurp = personFounded->CURP;
	string tempRfc = personFounded->RFC;
	string tempFecha = personFounded->fechaNaci;
	string tempCalle = personFounded->calle;
	string tempColonia = personFounded->colonia;
	string tempCiudad = personFounded->ciudad;
	string tempEstado = personFounded->estado;
	string tempCivil = personFounded->estadoCivil;
	string tempTelefo = personFounded->telefono;
	string tempSexo = personFounded->sexo;
	string tempGrupo = personFounded->grupoOcup;
	string tempPerfil = personFounded->perfilRies;
	string tempIdentiti = personFounded->identiString;
	strcpy_s(ApPersonC, tempApPerson.c_str());
	SetWindowText(hApPerson, ApPersonC);
	strcpy_s(AmPersonC, tempAmPerson.c_str());
	SetWindowText(hAmPerson, AmPersonC);
	strcpy_s(NameC, tempName.c_str());
	SetWindowText(hName, NameC);
	strcpy_s(CurpC, tempCurp.c_str());
	SetWindowText(hCurp, CurpC);
	strcpy_s(RfcC, tempRfc.c_str());
	SetWindowText(hRfc, RfcC);
	strcpy_s(FechaC, tempFecha.c_str());
	SetWindowText(hFecha, FechaC);
	strcpy_s(CalleC, tempCalle.c_str());
	SetWindowText(hCalle, CalleC);
	strcpy_s(ColoniaC, tempColonia.c_str());
	SetWindowText(hColonia, ColoniaC);
	strcpy_s(CiudadC, tempCiudad.c_str());
	SetWindowText(hCiudad, CiudadC);
	strcpy_s(EstadoC, tempEstado.c_str());
	SetWindowText(hEstado, EstadoC);
	strcpy_s(CivilC, tempCivil.c_str());
	SetWindowText(hCivil, CivilC);
	strcpy_s(TelefoC, tempTelefo.c_str());
	SetWindowText(hTelefo, TelefoC);
	strcpy_s(SexoC, tempSexo.c_str());
	SetWindowText(hSexo, SexoC);
	strcpy_s(GrupoC, tempGrupo.c_str());
	SetWindowText(hGrupo, GrupoC);
	strcpy_s(PerfilC, tempPerfil.c_str());
	SetWindowText(hPerfil, PerfilC);
	strcpy_s(IdentitiC, tempIdentiti.c_str());
	SetWindowText(hIdentiti, IdentitiC);
	string imageTemp = personFounded->identificacion;
	HWND hPBImage = GetDlgItem(hwnd, BM_IMAGE_PERSONDELETE);
	HBITMAP hImage = (HBITMAP)LoadImage(NULL, imageTemp.c_str(), IMAGE_BITMAP, 200, 200, LR_LOADFROMFILE);
	SendMessage(hPBImage, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hImage);
}

void showVariablesPersonChange(HWND hwnd) {
	HWND lb = GetDlgItem(hwnd, LB_CHANGE_PERSON);
	int contador = SendMessage(lb, LB_GETCOUNT, 0, 0);
	int selec = -1;
	for (int i = 0; i < contador; i++) {
		if (SendMessage(lb, LB_GETSEL, i, 0) > 0) {
			selec = i;
			break;
		}
	}
	char tempP[40];
	SendMessage(lb, LB_GETTEXT, selec, (LPARAM)tempP);
	string textPerson(tempP);
	Person* personFounded = searchPersonLB(textPerson);
	HWND hApPerson = GetDlgItem(hwnd, TXT_AP_PERSONCHANGE);
	HWND hAmPerson = GetDlgItem(hwnd, TXT_AM_PERSONCHANGE);
	HWND hName = GetDlgItem(hwnd, TXT_NAME_PERSONCHANGE);
	HWND hCurp = GetDlgItem(hwnd, TXT_CURP_PERSONCHANGE);
	HWND hRfc = GetDlgItem(hwnd, TXT_RFC_PERSONCHANGE);
	HWND hFecha = GetDlgItem(hwnd, TXT_FECHA_PERSONCHANGE);
	HWND hCalle = GetDlgItem(hwnd, TXT_CALLE_PERSONCHANGE);
	HWND hColonia = GetDlgItem(hwnd, TXT_COLONIA_PERSONCHANGE);
	HWND hCiudad = GetDlgItem(hwnd, TXT_CIUDAD_PERSONCHANGE);
	HWND hEstado = GetDlgItem(hwnd, TXT_ESTADO_PERSONCHANGE);
	HWND hCivil = GetDlgItem(hwnd, TXT_CIVIL_PERSONCHANGE);
	HWND hTelefo = GetDlgItem(hwnd, TXT_TELEFO_PERSONCHANGE);
	HWND hSexo = GetDlgItem(hwnd, TXT_SEXO_PERSONCHANGE);
	HWND hGrupo = GetDlgItem(hwnd, TXT_GRUPO_PERSONCHANGE);
	HWND hPerfil = GetDlgItem(hwnd, TXT_PERFIL_PERSONCHANGE);
	HWND hIdentiti = GetDlgItem(hwnd, TXT_IDENTIDAD_PERSONCHANGE);
	char ApPersonC[20], AmPersonC[20], NameC[20], CurpC[20], RfcC[20], FechaC[20], CalleC[20];
	char ColoniaC[20], CiudadC[20], EstadoC[20], CivilC[20], TelefoC[20], SexoC[20];
	char GrupoC[20], PerfilC[20], IdentitiC[10];
	string tempApPerson = personFounded->apPerson;
	string tempAmPerson = personFounded->amPerson;
	string tempName = personFounded->namePerson;
	string tempCurp = personFounded->CURP;
	string tempRfc = personFounded->RFC;
	string tempFecha = personFounded->fechaNaci;
	string tempCalle = personFounded->calle;
	string tempColonia = personFounded->colonia;
	string tempCiudad = personFounded->ciudad;
	string tempEstado = personFounded->estado;
	string tempCivil = personFounded->estadoCivil;
	string tempTelefo = personFounded->telefono;
	string tempSexo = personFounded->sexo;
	string tempGrupo = personFounded->grupoOcup;
	string tempPerfil = personFounded->perfilRies;
	string tempIdentiti = personFounded->identiString;
	strcpy_s(ApPersonC, tempApPerson.c_str());
	SetWindowText(hApPerson, ApPersonC);
	strcpy_s(AmPersonC, tempAmPerson.c_str());
	SetWindowText(hAmPerson, AmPersonC);
	strcpy_s(NameC, tempName.c_str());
	SetWindowText(hName, NameC);
	strcpy_s(CurpC, tempCurp.c_str());
	SetWindowText(hCurp, CurpC);
	strcpy_s(RfcC, tempRfc.c_str());
	SetWindowText(hRfc, RfcC);
	strcpy_s(FechaC, tempFecha.c_str());
	SetWindowText(hFecha, FechaC);
	strcpy_s(CalleC, tempCalle.c_str());
	SetWindowText(hCalle, CalleC);
	strcpy_s(ColoniaC, tempColonia.c_str());
	SetWindowText(hColonia, ColoniaC);
	strcpy_s(CiudadC, tempCiudad.c_str());
	SetWindowText(hCiudad, CiudadC);
	strcpy_s(EstadoC, tempEstado.c_str());
	SetWindowText(hEstado, EstadoC);
	strcpy_s(CivilC, tempCivil.c_str());
	SetWindowText(hCivil, CivilC);
	strcpy_s(TelefoC, tempTelefo.c_str());
	SetWindowText(hTelefo, TelefoC);
	strcpy_s(SexoC, tempSexo.c_str());
	SetWindowText(hSexo, SexoC);
	strcpy_s(GrupoC, tempGrupo.c_str());
	SetWindowText(hGrupo, GrupoC);
	strcpy_s(PerfilC, tempPerfil.c_str());
	SetWindowText(hPerfil, PerfilC);
	strcpy_s(IdentitiC, tempIdentiti.c_str());
	SetWindowText(hIdentiti, IdentitiC);
	string imageTemp = personFounded->identificacion;
	HWND hPBImage = GetDlgItem(hwnd, BM_IMAGE_PERSONCHANGE);
	HBITMAP hImage = (HBITMAP)LoadImage(NULL, imageTemp.c_str(), IMAGE_BITMAP, 200, 200, LR_LOADFROMFILE);
	SendMessage(hPBImage, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hImage);
	pImageTempPerson = imageTemp;
	idPersonFounded = pAux->idPerson;
}

Person* searchPersonLB(string curp) {
	bool searchFound = true;
	pAux = pOrigin;
	while (curp.compare(pAux->CURP) != 0) {
		if (pAux->nextP == NULL) {
			searchFound = false;
			break;
		}
		pAux = pAux->nextP;
	}
	if (searchFound == false) {
		return NULL;
	}
	return pAux;
}

Person* searchPerson(string curp, Person* pAux) {
	bool searchFound = true;
	while (curp.compare(pAux->CURP) != 0) {
		if (pAux->nextP == NULL) {
			searchFound = false;
			break;
		}
		pAux = pAux->nextP;
	}
	if (searchFound == false) {
		return NULL;
	}
	return pAux;
}

void borrarPerson() {
	if (pAux->nextP == NULL && pAux->prevP == NULL) {
		delete pAux;
		pAux = pOrigin = NULL;
	}
	else if (pAux->prevP == NULL) {
		pOrigin = pOrigin->nextP;
		pOrigin->prevP = NULL;
		delete pAux;
		pAux = pOrigin;
	}
	else if (pAux->nextP == NULL) {
		pAux->prevP->nextP = NULL;

		delete pAux;
		pAux = pOrigin;
	}
	else {

		pAux->prevP->nextP = pAux->nextP;

		pAux->nextP->prevP = pAux->prevP;

		delete pAux;
		pAux = pOrigin;
	}
}

Person* searchPersonWithId(int id, Person* pAux) {
	bool searchFound = true;
	while ((id != pAux->idPerson) != 0) {

		if (pAux->nextP == NULL) {
			searchFound = false;
			break;
		}
		pAux = pAux->nextP;
	}
	if (searchFound == false) {
		return NULL;
	}
	return pAux;
}

bool searchPersonCopy2(string curp, string rfc, Person* pAux) {
	pAux = pOrigin;
	bool find = true;
	while (pAux->RFC.compare(rfc) != 0) {
		if (pAux->nextP == NULL) {
			pAux = pOrigin;
			return false;
		}
		pAux = pAux->nextP;
	}
	pAux = pOrigin;
	while (curp.compare(pAux->CURP) != 0) {
		if (pAux->nextP == NULL) {
			pAux = pOrigin;
			return false;
		}
		pAux = pAux->nextP;
	}
	pAux = pOrigin;
	return true;
}

Person* changePerson(Person* pAux, string ap, string am, string name, string curp, string rfc, string fecha, string calle, string colonia, string ciudad, string estado, string civil, string telefono, string sexo, string grupo, string perfil, string identiti) {
	pAux->apPerson = ap;
	pAux->amPerson = am;
	pAux->namePerson = name;
	strcpy_s(pAux->CURP, curp.c_str());
	pAux->RFC = rfc;
	pAux->fechaNaci = fecha;
	pAux->calle = calle;
	pAux->colonia = colonia;
	pAux->ciudad = ciudad;
	pAux->estado = estado;
	pAux->estadoCivil = civil;
	pAux->telefono = telefono;
	pAux->sexo = sexo;
	pAux->grupoOcup = grupo;
	pAux->perfilRies = perfil;
	strcpy_s(pAux->identificacion, pImageTempPerson.c_str());
	pAux->identiString = identiti;

	return pAux;
}

void showVariablesCarnetCurpRe(HWND hwnd) {
	HWND lb = GetDlgItem(hwnd, LB_CURP_RE_CARNET);
	int contador = SendMessage(lb, LB_GETCOUNT, 0, 0);
	int selec = -1;
	for (int i = 0; i < contador; i++) {
		if (SendMessage(lb, LB_GETSEL, i, 0) > 0) {
			selec = i;
			break;
		}
	}
	char tempP[40];
	SendMessage(lb, LB_GETTEXT, selec, (LPARAM)tempP);
	string textPerson(tempP);
	Person* personFounded = searchPersonLB(textPerson);
	HWND hApPerson = GetDlgItem(hwnd, TXT_AP_RE_CARNET);
	HWND hAmPerson = GetDlgItem(hwnd, TXT_AM_RE_CARNET);
	HWND hName = GetDlgItem(hwnd, TXT_NAME_RE_CARNET);
	HWND hCurp = GetDlgItem(hwnd, TXT_CURP_RE_CARNET);
	HWND hRfc = GetDlgItem(hwnd, TXT_RFC_RE_CARNET);
	HWND hFecha = GetDlgItem(hwnd, TXT_FECHA_RE_CARNET);
	HWND hCalle = GetDlgItem(hwnd, TXT_CALLE_RE_CARNET);
	HWND hColonia = GetDlgItem(hwnd, TXT_COLONIA_RE_CARNET);
	HWND hCiudad = GetDlgItem(hwnd, TXT_CIUDAD_RE_CARNET);
	HWND hEstado = GetDlgItem(hwnd, TXT_ESTADO_RE_CARNET);
	HWND hCivil = GetDlgItem(hwnd, TXT_CIVIL_RE_CARNET);
	HWND hTelefo = GetDlgItem(hwnd, TXT_TELEFO_RE_CARNET);
	HWND hSexo = GetDlgItem(hwnd, TXT_SEXO_RE_CARNET);
	HWND hGrupo = GetDlgItem(hwnd, TXT_GRUPO_RE_CARNET);
	HWND hPerfil = GetDlgItem(hwnd, TXT_PERFIL_RE_CARNET);
	HWND hIdentiti = GetDlgItem(hwnd, TXT_IDENTITI_RE_CARNET);
	char ApPersonC[20], AmPersonC[20], NameC[20], CurpC[20], RfcC[20], FechaC[20], CalleC[20];
	char ColoniaC[20], CiudadC[20], EstadoC[20], CivilC[20], TelefoC[20], SexoC[20];
	char GrupoC[20], PerfilC[20], IdentitiC[10];
	string tempApPerson = personFounded->apPerson;
	string tempAmPerson = personFounded->amPerson;
	string tempName = personFounded->namePerson;
	string tempCurp = personFounded->CURP;
	string tempRfc = personFounded->RFC;
	string tempFecha = personFounded->fechaNaci;
	string tempCalle = personFounded->calle;
	string tempColonia = personFounded->colonia;
	string tempCiudad = personFounded->ciudad;
	string tempEstado = personFounded->estado;
	string tempCivil = personFounded->estadoCivil;
	string tempTelefo = personFounded->telefono;
	string tempSexo = personFounded->sexo;
	string tempGrupo = personFounded->grupoOcup;
	string tempPerfil = personFounded->perfilRies;
	string tempIdentiti = personFounded->identiString;
	strcpy_s(ApPersonC, tempApPerson.c_str());
	SetWindowText(hApPerson, ApPersonC);
	strcpy_s(AmPersonC, tempAmPerson.c_str());
	SetWindowText(hAmPerson, AmPersonC);
	strcpy_s(NameC, tempName.c_str());
	SetWindowText(hName, NameC);
	strcpy_s(CurpC, tempCurp.c_str());
	SetWindowText(hCurp, CurpC);
	strcpy_s(RfcC, tempRfc.c_str());
	SetWindowText(hRfc, RfcC);
	strcpy_s(FechaC, tempFecha.c_str());
	SetWindowText(hFecha, FechaC);
	strcpy_s(CalleC, tempCalle.c_str());
	SetWindowText(hCalle, CalleC);
	strcpy_s(ColoniaC, tempColonia.c_str());
	SetWindowText(hColonia, ColoniaC);
	strcpy_s(CiudadC, tempCiudad.c_str());
	SetWindowText(hCiudad, CiudadC);
	strcpy_s(EstadoC, tempEstado.c_str());
	SetWindowText(hEstado, EstadoC);
	strcpy_s(CivilC, tempCivil.c_str());
	SetWindowText(hCivil, CivilC);
	strcpy_s(TelefoC, tempTelefo.c_str());
	SetWindowText(hTelefo, TelefoC);
	strcpy_s(SexoC, tempSexo.c_str());
	SetWindowText(hSexo, SexoC);
	strcpy_s(GrupoC, tempGrupo.c_str());
	SetWindowText(hGrupo, GrupoC);
	strcpy_s(PerfilC, tempPerfil.c_str());
	SetWindowText(hPerfil, PerfilC);
	strcpy_s(IdentitiC, tempIdentiti.c_str());
	SetWindowText(hIdentiti, IdentitiC);
	string imageTemp = personFounded->identificacion;
	HWND hPBImage = GetDlgItem(hwnd, BM_IMAGE_RE_CARNET);
	HBITMAP hImage = (HBITMAP)LoadImage(NULL, imageTemp.c_str(), IMAGE_BITMAP, 200, 200, LR_LOADFROMFILE);
	SendMessage(hPBImage, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hImage);
	pImageTempPerson = imageTemp;
}

void showVariablesCarnetClaveRe(HWND hwnd) {
	HWND lb = GetDlgItem(hwnd, LB_CLAVE_RE_CARNET);
	int contador = SendMessage(lb, LB_GETCOUNT, 0, 0);
	int selec = -1;
	for (int i = 0; i < contador; i++) {
		if (SendMessage(lb, LB_GETSEL, i, 0) > 0) {
			selec = i;
			break;
		}
	}
	char tempV[40];
	SendMessage(lb, LB_GETTEXT, selec, (LPARAM)tempV);
	string textVaccine(tempV);
	Vaccine* vaccineFounded = searchVacineLB(textVaccine);
	HWND htipo = GetDlgItem(hwnd, TXT_TIPO_RE_CARNET);
	HWND hmarca = GetDlgItem(hwnd, TXT_MARCA_RE_CARNET);
	HWND hdosis = GetDlgItem(hwnd, TXT_DOSIS_RE_CARNET);
	HWND hclave = GetDlgItem(hwnd, TXT_CLAVE_RE_CARNET);
	HWND hdescripcion = GetDlgItem(hwnd, TXT_DES_RE_CARNET);
	HWND hprecio = GetDlgItem(hwnd, TXT_PRECIO_RE_CARNET);
	char tipoC[20], marcaC[20], dosisC[20], claveC[20], descripC[40], precioC[10];
	string tempTipo = vaccineFounded->tipo;
	string tempMarca = vaccineFounded->marca;
	string tempDosis = vaccineFounded->dosis;
	string tempClave = vaccineFounded->claveVaccine;
	string tempDes = vaccineFounded->description;
	float tempPrecio = vaccineFounded->precio;
	strcpy_s(tipoC, tempTipo.c_str());
	SetWindowText(htipo, tipoC);
	strcpy_s(marcaC, tempMarca.c_str());
	SetWindowText(hmarca, marcaC);
	strcpy_s(dosisC, tempDosis.c_str());
	SetWindowText(hdosis, dosisC);
	strcpy_s(claveC, tempClave.c_str());
	SetWindowText(hclave, claveC);
	strcpy_s(descripC, tempDes.c_str());
	SetWindowText(hdescripcion, descripC);
	_itoa_s(tempPrecio, precioC, 10);
	SetWindowText(hprecio, precioC);
	dosisGlobal = tempDosis;
}

void fechaDosisVacuna(HWND hwnd, int fecha1, int fecha2) {
	//FECHA DEL SISTEMA
	int iYear = tiempo->tm_year + 1900;
	int iMonth = tiempo->tm_mon + 1;
	int iDay = tiempo->tm_mday;
	char cYear[5];
	char cMonth[5];
	char cDay[5];
	char cYear2[5];
	char cMonth2[5];
	char cDay2[5];
	_itoa_s(iYear, cYear, 10);
	_itoa_s(iMonth, cMonth, 10);
	_itoa_s(iDay, cDay, 10);
	string fechaDelSistema;
	fechaDelSistema.append(cDay);
	fechaDelSistema.append("/");
	fechaDelSistema.append(cMonth);
	fechaDelSistema.append("/");
	fechaDelSistema.append(cYear);
	HWND hFecha1 = GetDlgItem(hwnd, fecha1);
	SetWindowText(hFecha1, fechaDelSistema.c_str());

	for (int i = 0; i < 30; i++) {
		iDay++;
		if (iDay > day_month(iMonth, iYear)) {
			iDay = 1;
			iMonth++;
			if (iMonth > 12) {
				iMonth = 1;
				iYear++;
			}
		}
	}
	int comparison = stoi(dosisGlobal);
	if (comparison == 2) {
		_itoa_s(iYear, cYear2, 10);
		_itoa_s(iMonth, cMonth2, 10);
		_itoa_s(iDay, cDay2, 10);
		string fechaSumada;
		fechaSumada.append(cDay2);
		fechaSumada.append("/");
		fechaSumada.append(cMonth2);
		fechaSumada.append("/");
		fechaSumada.append(cYear2);
		HWND hFecha2 = GetDlgItem(hwnd, fecha2);
		SetWindowText(hFecha2, fechaSumada.c_str());
	}
	else {
		HWND hFecha2 = GetDlgItem(hwnd, fecha2);
		SetWindowText(hFecha2, "No aplica");
	}
}

int day_month(int month, int year) {
	int days = 31;
	if (month == 4 || month == 6 || month == 9 || month == 11) {
		days = 30;
	}
	else if (month == 2) {
		if (bisiesto(year)) {
			days = 29;
		}
		else {
			days = 28;
		}
	}
	return days;
}

bool bisiesto(int year) {
	return ((year % 4) == 0 && (year % 100) != 0) || ((year % 400) == 0);
}

void habilitarBoton(bool check1, bool check2, HWND hwnd) {
	if (check1 == true && check2 == true) {
		HWND btnOk = GetDlgItem(hwnd, BTN_OK_RE_CARNET);
		EnableWindow(btnOk, true);
	}
}

void borrarCarnet() {
	if (cAux->nextC == NULL && cAux->prevC == NULL) {
		delete cAux;
		cAux = cOrigin = NULL;
	}
	else if (cAux->prevC == NULL) {
		cOrigin = cOrigin->nextC;
		cOrigin->prevC = NULL;
		delete cAux;
		cAux = cOrigin;
	}
	else if (cAux->nextC == NULL) {
		cAux->prevC->nextC = NULL;

		delete cAux;
		cAux = cOrigin;
	}
	else {

		cAux->prevC->nextC = cAux->nextC;

		cAux->nextC->prevC = cAux->prevC;

		delete cAux;
		cAux = cOrigin;
	}
}

Carnet* busquedaBinaria(Carnet* cOrigin, int id) {
	Carnet* start = cOrigin;
	Carnet* last = NULL;
	do
	{
		Carnet* mid = findMid(start, last);
		if (mid == NULL) {
			return NULL;
		}
		if (mid->idCarnet == id) {
			return mid;
		}
		else if (mid->idCarnet < id) {
			start = mid->nextC;
		}
		else {
			last = mid;
		}

	} while (last == NULL || last != start);
	return NULL;
}

Carnet* findMid(Carnet* start, Carnet* last) {
	if (start == NULL) {
		return NULL;
	}
	Carnet* actual = start;
	Carnet* futuro = start->nextC;
	while (futuro != last) {
		futuro = futuro->nextC;
		if (futuro != last) {
			actual = actual->nextC;
			futuro = futuro->nextC;
		}
	}
	return actual;
}

void showVariablesCarnetDelete(HWND hwnd) {
	HWND hAp = GetDlgItem(hwnd, TXT_AP_DELETE_CARNET);
	HWND hAm = GetDlgItem(hwnd, TXT_AM_DELETE_CARNET);
	HWND hName = GetDlgItem(hwnd, TXT_NAME_DELETE_CARNET);
	HWND hCurp = GetDlgItem(hwnd, TXT_CURP_DELETE_CARNET);
	HWND hRfc = GetDlgItem(hwnd, TXT_RFC_DELETE_CARNET);
	HWND hFechaNaci = GetDlgItem(hwnd, TXT_FECHA_DELETE_CARNET);
	HWND hCalle = GetDlgItem(hwnd, TXT_CALLE_DELETE_CARNET);
	HWND hColonia = GetDlgItem(hwnd, TXT_COLONIA_DELETE_CARNET);
	HWND hCiudad = GetDlgItem(hwnd, TXT_CIUDAD_DELETE_CARNET);
	HWND hEstado = GetDlgItem(hwnd, TXT_ESTADO_DELETE_CARNET);
	HWND hCivil = GetDlgItem(hwnd, TXT_CIVIL_DELETE_CARNET);
	HWND hTelefo = GetDlgItem(hwnd, TXT_TELEFO_DELETE_CARNET);
	HWND hSexo = GetDlgItem(hwnd, TXT_SEXO_DELETE_CARNET);
	HWND hGrupo = GetDlgItem(hwnd, TXT_GRUPO_DELETE_CARNET);
	HWND hPerfil = GetDlgItem(hwnd, TXT_PERFIL_DELETE_CARNET);
	HWND hCentro = GetDlgItem(hwnd, TXT_CENTRO_DELETE_CARNET);
	HWND hTipo = GetDlgItem(hwnd, TXT_TIPO_DELETE_CARNET);
	HWND hMarca = GetDlgItem(hwnd, TXT_MARCA_DELETE_CARNET);
	HWND hDosis = GetDlgItem(hwnd, TXT_DOSIS_DELETE_CARNET);
	HWND hClave = GetDlgItem(hwnd, TXT_CLAVE_DELETE_CARNET);
	HWND hDes = GetDlgItem(hwnd, TXT_DES_DELETE_CARNET);
	HWND hPrecio = GetDlgItem(hwnd, TXT_PRECIO_DELETE_CARNET);
	HWND hFecha = GetDlgItem(hwnd, TXT_FECHAVACU1_DELETE_CARNET);
	HWND hFecha2 = GetDlgItem(hwnd, TXT_FECHAVACU2_DELETE_CARNET);
	HWND hID = GetDlgItem(hwnd, TXT_ID_DELETE_CARNET);
	char ApPersonC[20], AmPersonC[20], NameC[20], CurpC[20], RfcC[20], FechaC[20], CalleC[20];
	char ColoniaC[20], CiudadC[20], EstadoC[20], CivilC[20], TelefoC[20], SexoC[20];
	char GrupoC[20], PerfilC[20], Centro[10], fecha[20], fecha2[20], idC[3];
	char tipoC[20], marcaC[20], dosisC[20], claveC[20], descripC[40], precioC[10];
	string tempApPerson = carnetFounded->apPersonCar;
	string tempAmPerson = carnetFounded->amPersonCar;
	string tempName = carnetFounded->namePersonCar;
	string tempCurp = carnetFounded->curpCarnet;
	string tempRfc = carnetFounded->RFCCar;
	string tempFecha = carnetFounded->fechaNaciCar;
	string tempCalle = carnetFounded->calleCar;
	string tempColonia = carnetFounded->coloniaCar;
	string tempCiudad = carnetFounded->ciudadCar;
	string tempEstado = carnetFounded->estadoCar;
	string tempCivil = carnetFounded->estadoCivilCar;
	string tempTelefo = carnetFounded->telefonoCar;
	string tempSexo = carnetFounded->sexoCar;
	string tempGrupo = carnetFounded->grupoOcupCar;
	string tempPerfil = carnetFounded->perfilRiesCar;
	string tempCentro = carnetFounded->centroDeVacu;
	string tempTipo = carnetFounded->loteMarca;
	string tempMarca = carnetFounded->vacunaCarnet;
	string tempDosis = carnetFounded->dosisCarnet;
	string tempClave = carnetFounded->claveVaccineCar;
	string tempDes = carnetFounded->descriptionCar;
	float tempPrecio = carnetFounded->precioCar;
	string tempFecha1 = carnetFounded->fechaDosisCarnet;
	string tempFecha2 = carnetFounded->fechaDosisCarnet2;
	int tempID = carnetFounded->idCarnet;
	string imageTemp = carnetFounded->identificacionCar;
	string idString = to_string(tempID);
	strcpy_s(fecha, tempFecha1.c_str());
	SetWindowText(hFecha, fecha);
	strcpy_s(fecha2, tempFecha2.c_str());
	SetWindowText(hFecha2, fecha2);
	strcpy_s(Centro, tempCentro.c_str());
	SetWindowText(hCentro, Centro);
	strcpy_s(idC, idString.c_str());
	SetWindowText(hID, idC);
	strcpy_s(ApPersonC, tempApPerson.c_str());
	SetWindowText(hAp, ApPersonC);
	strcpy_s(AmPersonC, tempAmPerson.c_str());
	SetWindowText(hAm, AmPersonC);
	strcpy_s(NameC, tempName.c_str());
	SetWindowText(hName, NameC);
	strcpy_s(CurpC, tempCurp.c_str());
	SetWindowText(hCurp, CurpC);
	strcpy_s(RfcC, tempRfc.c_str());
	SetWindowText(hRfc, RfcC);
	strcpy_s(FechaC, tempFecha.c_str());
	SetWindowText(hFechaNaci, FechaC);
	strcpy_s(CalleC, tempCalle.c_str());
	SetWindowText(hCalle, CalleC);
	strcpy_s(ColoniaC, tempColonia.c_str());
	SetWindowText(hColonia, ColoniaC);
	strcpy_s(CiudadC, tempCiudad.c_str());
	SetWindowText(hCiudad, CiudadC);
	strcpy_s(EstadoC, tempEstado.c_str());
	SetWindowText(hEstado, EstadoC);
	strcpy_s(CivilC, tempCivil.c_str());
	SetWindowText(hCivil, CivilC);
	strcpy_s(TelefoC, tempTelefo.c_str());
	SetWindowText(hTelefo, TelefoC);
	strcpy_s(SexoC, tempSexo.c_str());
	SetWindowText(hSexo, SexoC);
	strcpy_s(GrupoC, tempGrupo.c_str());
	SetWindowText(hGrupo, GrupoC);
	strcpy_s(PerfilC, tempPerfil.c_str());
	SetWindowText(hPerfil, PerfilC);
	strcpy_s(tipoC, tempTipo.c_str());
	SetWindowText(hTipo, tipoC);
	strcpy_s(marcaC, tempMarca.c_str());
	SetWindowText(hMarca, marcaC);
	strcpy_s(dosisC, tempDosis.c_str());
	SetWindowText(hDosis, dosisC);
	strcpy_s(claveC, tempClave.c_str());
	SetWindowText(hClave, claveC);
	strcpy_s(descripC, tempDes.c_str());
	SetWindowText(hDes, descripC);
	_itoa_s(tempPrecio, precioC, 10);
	SetWindowText(hPrecio, precioC);

	HWND hPBImage = GetDlgItem(hwnd, BM_IMAGE_DELETE_CARNET);
	HBITMAP hImage = (HBITMAP)LoadImage(NULL, imageTemp.c_str(), IMAGE_BITMAP, 200, 200, LR_LOADFROMFILE);
	SendMessage(hPBImage, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hImage);

}

void showVariablesCarnetChange(HWND hwnd) {
	HWND hAp = GetDlgItem(hwnd, TXT_AP_CHANGE_CARNET);
	HWND hAm = GetDlgItem(hwnd, TXT_AM_CHANGE_CARNET);
	HWND hName = GetDlgItem(hwnd, TXT_NAME_CHANGE_CARNET);
	HWND hCurp = GetDlgItem(hwnd, TXT_CURP_CHANGE_CARNET);
	HWND hRfc = GetDlgItem(hwnd, TXT_RFC_CHANGE_CARNET);
	HWND hFechaNaci = GetDlgItem(hwnd, TXT_FECHA_CHANGE_CARNET);
	HWND hCalle = GetDlgItem(hwnd, TXT_CALLE_CHANGE_CARNET);
	HWND hColonia = GetDlgItem(hwnd, TXT_COLONIA_CHANGE_CARNET);
	HWND hCiudad = GetDlgItem(hwnd, TXT_CIUDAD_CHANGE_CARNET);
	HWND hEstado = GetDlgItem(hwnd, TXT_ESTADO_CHANGE_CARNET);
	HWND hCivil = GetDlgItem(hwnd, TXT_CIVIL_CHANGE_CARNET);
	HWND hTelefo = GetDlgItem(hwnd, TXT_TELEFO_CHANGE_CARNET);
	HWND hSexo = GetDlgItem(hwnd, TXT_SEXO_CHANGE_CARNET);
	HWND hGrupo = GetDlgItem(hwnd, TXT_GRUPO_CHANGE_CARNET);
	HWND hPerfil = GetDlgItem(hwnd, TXT_PERFIL_CHANGE_CARNET);
	HWND hCentro = GetDlgItem(hwnd, TXT_CENTRO_CHANGE_CARNET);
	HWND hTipo = GetDlgItem(hwnd, TXT_TIPO_CHANGE_CARNET);
	HWND hMarca = GetDlgItem(hwnd, TXT_MARCA_CHANGE_CARNET);
	HWND hDosis = GetDlgItem(hwnd, TXT_DOSIS_CHANGE_CARNET);
	HWND hClave = GetDlgItem(hwnd, TXT_CLAVE_CHANGE_CARNET);
	HWND hDes = GetDlgItem(hwnd, TXT_DES_CHANGE_CARNET);
	HWND hPrecio = GetDlgItem(hwnd, TXT_PRECIO_CHANGE_CARNET);
	HWND hFecha = GetDlgItem(hwnd, TXT_FECHAVACU1_CHANGE_CARNET);
	HWND hFecha2 = GetDlgItem(hwnd, TXT_FECHAVACU2_CHANGE_CARNET);
	HWND hID = GetDlgItem(hwnd, TXT_ID_CHANGE_CARNET);
	HWND hIdentiti = GetDlgItem(hwnd, TXT_IDENTITI_CHANGE_CARNET);
	char ApPersonC[20], AmPersonC[20], NameC[20], CurpC[20], RfcC[20], FechaC[20], CalleC[20];
	char ColoniaC[20], CiudadC[20], EstadoC[20], CivilC[20], TelefoC[20], SexoC[20];
	char GrupoC[20], PerfilC[20], Centro[10], fecha[20], fecha2[20], idC[3];
	char tipoC[20], marcaC[20], dosisC[20], claveC[20], descripC[40], precioC[10], identitiC[5];
	string tempApPerson = carnetFounded->apPersonCar;
	string tempAmPerson = carnetFounded->amPersonCar;
	string tempName = carnetFounded->namePersonCar;
	string tempCurp = carnetFounded->curpCarnet;
	string tempRfc = carnetFounded->RFCCar;
	string tempFecha = carnetFounded->fechaNaciCar;
	string tempCalle = carnetFounded->calleCar;
	string tempColonia = carnetFounded->coloniaCar;
	string tempCiudad = carnetFounded->ciudadCar;
	string tempEstado = carnetFounded->estadoCar;
	string tempCivil = carnetFounded->estadoCivilCar;
	string tempTelefo = carnetFounded->telefonoCar;
	string tempSexo = carnetFounded->sexoCar;
	string tempGrupo = carnetFounded->grupoOcupCar;
	string tempPerfil = carnetFounded->perfilRiesCar;
	string tempCentro = carnetFounded->centroDeVacu;
	string tempTipo = carnetFounded->loteMarca;
	string tempMarca = carnetFounded->vacunaCarnet;
	string tempDosis = carnetFounded->dosisCarnet;
	string tempClave = carnetFounded->claveVaccineCar;
	string tempDes = carnetFounded->descriptionCar;
	float tempPrecio = carnetFounded->precioCar;
	string tempFecha1 = carnetFounded->fechaDosisCarnet;
	string tempFecha2 = carnetFounded->fechaDosisCarnet2;
	int tempID = carnetFounded->idCarnet;
	string imageTemp = carnetFounded->identificacionCar;
	string idString = to_string(tempID);
	string identitiTemp = carnetFounded->identiStringCar;
	strcpy_s(identitiC, identitiTemp.c_str());
	SetWindowText(hIdentiti, identitiC);
	strcpy_s(fecha, tempFecha1.c_str());
	SetWindowText(hFecha, fecha);
	strcpy_s(fecha2, tempFecha2.c_str());
	SetWindowText(hFecha2, fecha2);
	strcpy_s(Centro, tempCentro.c_str());
	SetWindowText(hCentro, Centro);
	strcpy_s(idC, idString.c_str());
	SetWindowText(hID, idC);
	strcpy_s(ApPersonC, tempApPerson.c_str());
	SetWindowText(hAp, ApPersonC);
	strcpy_s(AmPersonC, tempAmPerson.c_str());
	SetWindowText(hAm, AmPersonC);
	strcpy_s(NameC, tempName.c_str());
	SetWindowText(hName, NameC);
	strcpy_s(CurpC, tempCurp.c_str());
	SetWindowText(hCurp, CurpC);
	strcpy_s(RfcC, tempRfc.c_str());
	SetWindowText(hRfc, RfcC);
	strcpy_s(FechaC, tempFecha.c_str());
	SetWindowText(hFechaNaci, FechaC);
	strcpy_s(CalleC, tempCalle.c_str());
	SetWindowText(hCalle, CalleC);
	strcpy_s(ColoniaC, tempColonia.c_str());
	SetWindowText(hColonia, ColoniaC);
	strcpy_s(CiudadC, tempCiudad.c_str());
	SetWindowText(hCiudad, CiudadC);
	strcpy_s(EstadoC, tempEstado.c_str());
	SetWindowText(hEstado, EstadoC);
	strcpy_s(CivilC, tempCivil.c_str());
	SetWindowText(hCivil, CivilC);
	strcpy_s(TelefoC, tempTelefo.c_str());
	SetWindowText(hTelefo, TelefoC);
	strcpy_s(SexoC, tempSexo.c_str());
	SetWindowText(hSexo, SexoC);
	strcpy_s(GrupoC, tempGrupo.c_str());
	SetWindowText(hGrupo, GrupoC);
	strcpy_s(PerfilC, tempPerfil.c_str());
	SetWindowText(hPerfil, PerfilC);
	strcpy_s(tipoC, tempTipo.c_str());
	SetWindowText(hTipo, tipoC);
	strcpy_s(marcaC, tempMarca.c_str());
	SetWindowText(hMarca, marcaC);
	strcpy_s(dosisC, tempDosis.c_str());
	SetWindowText(hDosis, dosisC);
	strcpy_s(claveC, tempClave.c_str());
	SetWindowText(hClave, claveC);
	strcpy_s(descripC, tempDes.c_str());
	SetWindowText(hDes, descripC);
	_itoa_s(tempPrecio, precioC, 10);
	SetWindowText(hPrecio, precioC);

	HWND hPBImage = GetDlgItem(hwnd, BM_IMAGE_CHANGE_CARNET);
	HBITMAP hImage = (HBITMAP)LoadImage(NULL, imageTemp.c_str(), IMAGE_BITMAP, 200, 200, LR_LOADFROMFILE);
	SendMessage(hPBImage, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hImage);

}

void showVariablesCarnetCurpChange(HWND hwnd) {
	HWND lb = GetDlgItem(hwnd, LB_CURP_CHANGE_CARNET);
	int contador = SendMessage(lb, LB_GETCOUNT, 0, 0);
	int selec = -1;
	for (int i = 0; i < contador; i++) {
		if (SendMessage(lb, LB_GETSEL, i, 0) > 0) {
			selec = i;
			break;
		}
	}
	char tempP[40];
	SendMessage(lb, LB_GETTEXT, selec, (LPARAM)tempP);
	string textPerson(tempP);
	Person* personFounded = searchPersonLB(textPerson);
	HWND hApPerson = GetDlgItem(hwnd, TXT_AP_CHANGE_CARNET);
	HWND hAmPerson = GetDlgItem(hwnd, TXT_AM_CHANGE_CARNET);
	HWND hName = GetDlgItem(hwnd, TXT_NAME_CHANGE_CARNET);
	HWND hCurp = GetDlgItem(hwnd, TXT_CURP_CHANGE_CARNET);
	HWND hRfc = GetDlgItem(hwnd, TXT_RFC_CHANGE_CARNET);
	HWND hFecha = GetDlgItem(hwnd, TXT_FECHA_CHANGE_CARNET);
	HWND hCalle = GetDlgItem(hwnd, TXT_CALLE_CHANGE_CARNET);
	HWND hColonia = GetDlgItem(hwnd, TXT_COLONIA_CHANGE_CARNET);
	HWND hCiudad = GetDlgItem(hwnd, TXT_CIUDAD_CHANGE_CARNET);
	HWND hEstado = GetDlgItem(hwnd, TXT_ESTADO_CHANGE_CARNET);
	HWND hCivil = GetDlgItem(hwnd, TXT_CIVIL_CHANGE_CARNET);
	HWND hTelefo = GetDlgItem(hwnd, TXT_TELEFO_CHANGE_CARNET);
	HWND hSexo = GetDlgItem(hwnd, TXT_SEXO_CHANGE_CARNET);
	HWND hGrupo = GetDlgItem(hwnd, TXT_GRUPO_CHANGE_CARNET);
	HWND hPerfil = GetDlgItem(hwnd, TXT_PERFIL_CHANGE_CARNET);
	HWND hIdentiti = GetDlgItem(hwnd, TXT_IDENTITI_CHANGE_CARNET);
	char ApPersonC[20], AmPersonC[20], NameC[20], CurpC[20], RfcC[20], FechaC[20], CalleC[20];
	char ColoniaC[20], CiudadC[20], EstadoC[20], CivilC[20], TelefoC[20], SexoC[20];
	char GrupoC[20], PerfilC[20], IdentitiC[10];
	string tempApPerson = personFounded->apPerson;
	string tempAmPerson = personFounded->amPerson;
	string tempName = personFounded->namePerson;
	string tempCurp = personFounded->CURP;
	string tempRfc = personFounded->RFC;
	string tempFecha = personFounded->fechaNaci;
	string tempCalle = personFounded->calle;
	string tempColonia = personFounded->colonia;
	string tempCiudad = personFounded->ciudad;
	string tempEstado = personFounded->estado;
	string tempCivil = personFounded->estadoCivil;
	string tempTelefo = personFounded->telefono;
	string tempSexo = personFounded->sexo;
	string tempGrupo = personFounded->grupoOcup;
	string tempPerfil = personFounded->perfilRies;
	string tempIdentiti = personFounded->identiString;
	strcpy_s(ApPersonC, tempApPerson.c_str());
	SetWindowText(hApPerson, ApPersonC);
	strcpy_s(AmPersonC, tempAmPerson.c_str());
	SetWindowText(hAmPerson, AmPersonC);
	strcpy_s(NameC, tempName.c_str());
	SetWindowText(hName, NameC);
	strcpy_s(CurpC, tempCurp.c_str());
	SetWindowText(hCurp, CurpC);
	strcpy_s(RfcC, tempRfc.c_str());
	SetWindowText(hRfc, RfcC);
	strcpy_s(FechaC, tempFecha.c_str());
	SetWindowText(hFecha, FechaC);
	strcpy_s(CalleC, tempCalle.c_str());
	SetWindowText(hCalle, CalleC);
	strcpy_s(ColoniaC, tempColonia.c_str());
	SetWindowText(hColonia, ColoniaC);
	strcpy_s(CiudadC, tempCiudad.c_str());
	SetWindowText(hCiudad, CiudadC);
	strcpy_s(EstadoC, tempEstado.c_str());
	SetWindowText(hEstado, EstadoC);
	strcpy_s(CivilC, tempCivil.c_str());
	SetWindowText(hCivil, CivilC);
	strcpy_s(TelefoC, tempTelefo.c_str());
	SetWindowText(hTelefo, TelefoC);
	strcpy_s(SexoC, tempSexo.c_str());
	SetWindowText(hSexo, SexoC);
	strcpy_s(GrupoC, tempGrupo.c_str());
	SetWindowText(hGrupo, GrupoC);
	strcpy_s(PerfilC, tempPerfil.c_str());
	SetWindowText(hPerfil, PerfilC);
	strcpy_s(IdentitiC, tempIdentiti.c_str());
	SetWindowText(hIdentiti, IdentitiC);
	string imageTemp = personFounded->identificacion;
	HWND hPBImage = GetDlgItem(hwnd, BM_IMAGE_CHANGE_CARNET);
	HBITMAP hImage = (HBITMAP)LoadImage(NULL, imageTemp.c_str(), IMAGE_BITMAP, 200, 200, LR_LOADFROMFILE);
	SendMessage(hPBImage, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hImage);
	pImageTempPerson = imageTemp;
}

void showVariablesCarnetClaveChange(HWND hwnd) {
	HWND lb = GetDlgItem(hwnd, LB_CLAVE_CHANGE_CARNET);
	int contador = SendMessage(lb, LB_GETCOUNT, 0, 0);
	int selec = -1;
	for (int i = 0; i < contador; i++) {
		if (SendMessage(lb, LB_GETSEL, i, 0) > 0) {
			selec = i;
			break;
		}
	}
	char tempV[40];
	SendMessage(lb, LB_GETTEXT, selec, (LPARAM)tempV);
	string textVaccine(tempV);
	Vaccine* vaccineFounded = searchVacineLB(textVaccine);
	HWND htipo = GetDlgItem(hwnd, TXT_TIPO_CHANGE_CARNET);
	HWND hmarca = GetDlgItem(hwnd, TXT_MARCA_CHANGE_CARNET);
	HWND hdosis = GetDlgItem(hwnd, TXT_DOSIS_CHANGE_CARNET);
	HWND hclave = GetDlgItem(hwnd, TXT_CLAVE_CHANGE_CARNET);
	HWND hdescripcion = GetDlgItem(hwnd, TXT_DES_CHANGE_CARNET);
	HWND hprecio = GetDlgItem(hwnd, TXT_PRECIO_CHANGE_CARNET);
	char tipoC[20], marcaC[20], dosisC[20], claveC[20], descripC[40], precioC[10];
	string tempTipo = vaccineFounded->tipo;
	string tempMarca = vaccineFounded->marca;
	string tempDosis = vaccineFounded->dosis;
	string tempClave = vaccineFounded->claveVaccine;
	string tempDes = vaccineFounded->description;
	float tempPrecio = vaccineFounded->precio;
	strcpy_s(tipoC, tempTipo.c_str());
	SetWindowText(htipo, tipoC);
	strcpy_s(marcaC, tempMarca.c_str());
	SetWindowText(hmarca, marcaC);
	strcpy_s(dosisC, tempDosis.c_str());
	SetWindowText(hdosis, dosisC);
	strcpy_s(claveC, tempClave.c_str());
	SetWindowText(hclave, claveC);
	strcpy_s(descripC, tempDes.c_str());
	SetWindowText(hdescripcion, descripC);
	_itoa_s(tempPrecio, precioC, 10);
	SetWindowText(hprecio, precioC);
	dosisGlobal = tempDosis;
}

Carnet* changeCarnet(Carnet* cAux, string curpCar, string vacuCar, string dosisCar, string fechaCar, string fechaCar2, string loteCar, string centroVacu, string ap, string am, string name, string rfc, string fechaNaci, string calle, string colonia, string estado, string civil, string telefono, string ciudad, string sexo, string grupo, string perfil, string identiti, string clave, string des, float precio) {
	strcpy_s(cAux->curpCarnet, curpCar.c_str());
	cAux->vacunaCarnet = vacuCar;
	cAux->dosisCarnet = dosisCar;
	cAux->fechaDosisCarnet = fechaCar;
	cAux->fechaDosisCarnet2 = fechaCar2;
	cAux->loteMarca = loteCar;
	cAux->centroDeVacu = centroVacu;
	cAux->amPersonCar = am;
	cAux->apPersonCar = ap;
	cAux->namePersonCar = name;
	cAux->RFCCar = rfc;
	cAux->fechaNaciCar = fechaNaci;
	cAux->calleCar = calle;
	cAux->coloniaCar = colonia;
	cAux->estadoCar = estado;
	cAux->estadoCivilCar = civil;
	cAux->telefonoCar = telefono;
	cAux->ciudadCar = ciudad;
	cAux->sexoCar = sexo;
	cAux->grupoOcupCar = grupo;
	cAux->perfilRiesCar = perfil;
	cAux->identiStringCar = identiti;
	cAux->claveVaccineCar = clave;
	cAux->precioCar = precio;
	strcpy_s(cAux->descriptionCar, des.c_str());
	strcpy_s(cAux->identificacionCar, pImageTempPerson.c_str());
	return cAux;
}

string juntarTextoQuickSort(Carnet* cAux) {
	string person = cAux->namePersonCar;
	string ap = cAux->apPersonCar;
	string am = cAux->apPersonCar;
	string identiti = cAux->identiStringCar;
	string telefo = cAux->telefonoCar;
	string calle = cAux->calleCar;
	string colonia = cAux->coloniaCar;
	string ciudad = cAux->ciudadCar;
	string estado = cAux->estadoCar;
	string fechaNaci = cAux->fechaNaciCar;
	string sexo = cAux->sexoCar;
	string grupo = cAux->grupoOcupCar;
	string perfil = cAux->perfilRiesCar;
	person.append(" ").append(ap).append(" ").append(am).append(" ").append(identiti).append(" ").append(telefo).append(" ").append(calle).append(" ").append(colonia).append(" ").append(ciudad).append(" ").append(estado).append(" ").append(fechaNaci).append(" ").append(sexo).append(" ").append(grupo).append(" ").append(perfil).append("\n");
	return person;
}

string juntarTextoHeapSort(Carnet* cAux) {
	int id = cAux->idCarnet;
	string person = cAux->namePersonCar;
	string ap = cAux->apPersonCar;
	string am = cAux->apPersonCar;
	string identiti = cAux->identiStringCar;
	string telefo = cAux->telefonoCar;
	string calle = cAux->calleCar;
	string colonia = cAux->coloniaCar;
	string ciudad = cAux->ciudadCar;
	string estado = cAux->estadoCar;
	string fechaNaci = cAux->fechaNaciCar;
	string sexo = cAux->sexoCar;
	string grupo = cAux->grupoOcupCar;
	string perfil = cAux->perfilRiesCar;
	string idStr = to_string(id);
	idStr.append(" ").append(person).append(" ").append(ap).append(" ").append(am).append(" ").append(identiti).append(" ").append(telefo).append(" ").append(calle).append(" ").append(colonia).append(" ").append(ciudad).append(" ").append(estado).append(" ").append(fechaNaci).append(" ").append(sexo).append(" ").append(grupo).append(" ").append(perfil).append("\n");
	return idStr;
}
//Fue cambiada
void llenarReporteQuickSort(HWND hwnd, int id) {
	HWND hReporte = GetDlgItem(hwnd, id);
	char reportC[259];
	cAux = cOrigin;
	while (cAux != NULL) {
		string person = juntarTextoQuickSort(cAux);
		strcpy_s(reportC, person.c_str());
		SendMessage(hReporte, LB_ADDSTRING, NULL, (LPARAM)reportC);
		cAux = cAux->nextC;
	}
	cAux = cOrigin;
}
//Fue cambiada
void llenarReporteHeapSort(HWND hwnd, int id) {
	HWND hReporte = GetDlgItem(hwnd, id);
	char reportC[259];
	cAux = cOrigin;
	while (cAux != NULL) {
		string idStr = juntarTextoHeapSort(cAux);
		strcpy_s(reportC, idStr.c_str());
		SendMessage(hReporte, LB_ADDSTRING, NULL, (LPARAM)reportC);
		cAux = cAux->nextC;
	}
	cAux = cOrigin;
}

void saveMaxIdHeapSort() {
	fileManager.open("HeapSortId.txt", ios::out | ios::trunc);
	if (fileManager.is_open()) {
		fileManager << globalIdHeapSort;
		fileManager.close();
	}
	else {
		MessageBox(NULL, "No se pudo abrir el archivo de personas", "Aviso", MB_ICONWARNING);
	}
}

void saveMaxIdQuickSort() {
	fileManager.open("QuickSortId.txt", ios::out | ios::trunc);
	if (fileManager.is_open()) {
		fileManager << globalIdQuickSort;
		fileManager.close();
	}
	else {
		MessageBox(NULL, "No se pudo abrir el archivo de personas", "Aviso", MB_ICONWARNING);
	}
}

void getMaxIdHeapSort() {
	fileManager.open("HeapSortId.txt", ios::in);
	if (fileManager.is_open()) {
		fileManager >> globalIdHeapSort;
		fileManager.close();
	}
	else {
		//MessageBox(NULL, "No se pudo abrir el archivo de carnet", "Aviso", MB_ICONWARNING);
	}
}

void getMaxIdQuickSort() {
	fileManager.open("QuickSortId.txt", ios::in);
	if (fileManager.is_open()) {
		fileManager >> globalIdQuickSort;
		fileManager.close();
	}
	else {
		//MessageBox(NULL, "No se pudo abrir el archivo de carnet", "Aviso", MB_ICONWARNING);
	}
}

//void heapify(Carnet* head, int iteration) {
//	int par, node;
//	for (int i = 0; i <= iteration; i++) {
//		node = i;
//		par = (node == 0) ? 0 : (int)node / 2;
//		while (par >= 0 && node != 0) {
//			Carnet* nodo1 = recorreListaXVeces(par, head);
//			Carnet* nodo2 = recorreListaXVeces(par, head);
//			if (nodo1->idCarnet < nodo2->idCarnet) {
//				intercambiar(nodo1, nodo2);
//			}
//			node = par;
//			par = (node == 0) ? 0 : (int)node / 2;
//		}
//	}
//}
//
//void intercambiar(Carnet* node1, Carnet* node2) {
//	Carnet* temp;
//	temp = node1->nextC;
//	node1->nextC = node2->nextC;
//	node2->nextC = temp;
//	if (node1->nextC != NULL)
//		node1->nextC->prevC = node1;
//	if (node2->nextC != NULL)
//		node2->nextC->prevC = node2;
//	temp = node1->prevC;
//	node1->prevC = node2->prevC;
//	node2->prevC = temp;
//	if (node1->prevC != NULL)
//		node1->prevC->nextC = node1;
//	if (node2->prevC != NULL)
//		node2->prevC->nextC = node2;
//}
//
//Carnet* recorreListaXVeces(int i, Carnet* aux) {
//	for (int j = 0; j <= i; j++) {
//		aux = aux->nextC;
//	}
//	return aux;
//}
//
//void heapSort(Carnet* head, int size) {
//	for (int i = size - 1; i >= 0; i--) {
//		heapify(head, i);
//		Carnet* nodoAux = recorreListaXVeces(i, head);
//		intercambiar(head, nodoAux);
//	}
//}
//
//int countElementsList(Carnet* aux) {
//	int counter = 0;
//	while (aux != NULL) {
//		aux = aux->nextC;
//		counter++;
//	}
//	return counter;
//}

void reportHeapSort(int cant, int* infoHeap, HWND hwnd, int id) {
	HWND hReporte = GetDlgItem(hwnd, id);
	char reportC[259];
	cAux = cOrigin;
	while (cAux != NULL) {
		infoHeap[cant] = cAux->idCarnet;
		cant++;
		cAux = cAux->nextC;
	}
	cAux = cOrigin;
	heapSort(infoHeap, cant - 1);
	for (int i = 0; i < cant; i++) {
		while (cAux != NULL) {
			if (infoHeap[i] == cAux->idCarnet) {
				string idStr = juntarTextoHeapSort(cAux);
				strcpy_s(reportC, idStr.c_str());
				SendMessage(hReporte, LB_ADDSTRING, NULL, (LPARAM)reportC);
			}
			cAux = cAux->nextC;
		}
		cAux = cOrigin;
	}
	cAux = cOrigin;
}

void heapify(int* infoHeap, int cant) {
	int i, par, node;
	for (i = 1; i <= cant; i++) {
		node = i;
		par = (int)node / 2;
		while (par >= 1) {
			if (infoHeap[par] < infoHeap[node])
				swap(infoHeap[par], infoHeap[node]);
			node = par;
			par = (int)node / 2;
		}
	}
}

void heapSort(int* infoHeap, int cant) {
	for (int i = cant; i >= 1; i--){
		heapify(infoHeap, i);
		swap(infoHeap[1], infoHeap[i]);
	}
}

void reportQuickSort(int cant, string* infoQuick, HWND hwnd, int id) {
	HWND hReporte = GetDlgItem(hwnd, id);
	char reportC[259];
	cAux = cOrigin;
	while (cAux != NULL) {
		infoQuick[cant] = cAux->namePersonCar + " " + cAux->apPersonCar + " " + cAux->amPersonCar;
		cant++;
		cAux = cAux->nextC;
	}
	cAux = cOrigin;
	Quicksort(infoQuick, 0, cant);

	for (int i = 1; i <= cant; i++) {
		while (cAux != NULL) {
			if (infoQuick[i] == cAux->namePersonCar + " " + cAux->apPersonCar + " " + cAux->amPersonCar) {
				string idStr = juntarTextoQuickSort(cAux);
				strcpy_s(reportC, idStr.c_str());
				SendMessage(hReporte, LB_ADDSTRING, NULL, (LPARAM)reportC);
			}
			cAux = cAux->nextC;
		}
		cAux = cOrigin;
	}
	cAux = cOrigin;
}

void Quicksort(string* info, int primero, int ultimo){
	if (primero < ultimo)
	{
		int index = Partition(info, primero, ultimo);

		Quicksort(info, primero, index - 1);
		Quicksort(info, index + 1, ultimo);
	}
}

int Partition(string* info, int primero, int ultimo)
{
	int index = primero;
	string pivot = info[ultimo];
	string dinamic;

	for (int i = primero; i < ultimo; i++)
	{
		if (info[i] <= pivot)
		{
			dinamic = info[i];
			info[i] = info[index];
			info[index] = dinamic;
			index++;
		}
	}
	dinamic = info[ultimo];
	info[ultimo] = info[index];
	info[index] = dinamic;

	return index;
}

void reportHeapSortTxt(int id) {
	int cant = 0;
	int infoHeap[MAX_PATH];
	ofstream archivo;
	string nombreArchivo = "ReporteHeapSort";
	string idArc = to_string(id);
	nombreArchivo.append(idArc).append(".txt");
	archivo.open(nombreArchivo.c_str(), ios::out);
	if (archivo.fail()) {
		//EL MENSAJE DE TEXTO
		return;
	}
	cAux = cOrigin;
	while (cAux != NULL) {
		infoHeap[cant] = cAux->idCarnet;
		cant++;
		cAux = cAux->nextC;
	}
	cAux = cOrigin;
	heapSort(infoHeap, cant - 1);
	for (int i = 0; i < cant; i++) {
		while (cAux != NULL) {
			if (infoHeap[i] == cAux->idCarnet) {
				string idStr = juntarTextoHeapSort(cAux);
				archivo << idStr << endl;
			}
			cAux = cAux->nextC;
		}
		cAux = cOrigin;
	}
	archivo.close();
	cAux = cOrigin;
}

void reportQuickSortTxt(int id) {
	int cant = 0;
	string infoQuick[MAX_PATH];
	ofstream archivo;
	string nombreArchivo = "ReporteQuickSort";
	string idArc = to_string(id);
	nombreArchivo.append(idArc).append(".txt");
	archivo.open(nombreArchivo.c_str(), ios::out);
	if (archivo.fail()) {
		//EL MENSAJE DE TEXTO
		return;
	}
	cAux = cOrigin;
	while (cAux != NULL) {
		infoQuick[cant] = cAux->namePersonCar + " " + cAux->apPersonCar + " " + cAux->amPersonCar;
		cant++;
		cAux = cAux->nextC;
	}
	cAux = cOrigin;
	Quicksort(infoQuick, 0, cant);
	for (int i = 0; i < cant; i++) {
		while (cAux != NULL) {
			if (infoQuick[i] == cAux->namePersonCar + " " + cAux->apPersonCar + " " + cAux->amPersonCar) {
				string idStr = juntarTextoQuickSort(cAux);
				archivo << idStr << endl;
			}
			cAux = cAux->nextC;
		}
		cAux = cOrigin;
	}
	archivo.close();
	cAux = cOrigin;
}
#pragma endregion