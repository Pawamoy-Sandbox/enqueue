#include "mod.h"

/**
 *	\fn	void ModeRaw(int activer)
 *	\brief	Active ou désactive le mode Raw.
 *	Activer le mode Raw permet de récupérer les appuis de touche
 * 	du clavier sans avoir à appuyer sur Entrée. 
 *	Vous devez commencer votre programme en activant le mode Raw,
 *	et le désactiver avant de terminer le programme.
 *	\param	activer	0 pour désactiver, autre pour activer.
 *	\see	void ActiverModeRaw()
 *	\see	void DesactiverModeRaw()
 *	\see	int RecupererAppuiTouche()
 */
void ModeRaw(int activer){
	static struct termios cooked;
	static int raw_actif = 0;
	
	if (raw_actif == activer)
		return;
	
	if (activer)
	{
		struct termios raw;
		
		tcgetattr(STDIN_FILENO, &cooked);
		
		raw = cooked;
		cfmakeraw(&raw);
		tcsetattr(STDIN_FILENO, TCSANOW, &raw);
	}
	else
		tcsetattr(STDIN_FILENO, TCSANOW, &cooked);
	
	raw_actif = activer;
}

/**
 *	\fn	void ActiverModeRaw()
 *	\brief	Active le mode Raw.
 *	\see	int ModeRaw()
 */
void ActiverModeRaw(){
	ModeRaw(1);
}

/**
 *	\fn	void ActiverModeRaw()
 *	\brief	Désactive le mode Raw.
 *	\see	int ModeRaw()
 */
void DesactiverModeRaw(){
	ModeRaw(0);
}

/**
 *	\fn		void EffacerEcran();
 *	\brief	Efface la console.
 */
void EffacerEcran(){
	printf("\033[H\033[2J");
}

/**
 *	\fn		void ChangerCouleurTexte(int couleur)
 *	\brief	Change la couleur courante du texte.
 *	\param	couleur	La nouvelle couleur de texte.
 */
void ChangerCouleurTexte(int couleur){
	printf("\033[%dm",couleur);
}

/**
 *	\fn		void ChangerCouleurFond(int couleur)
 *	\brief	Change la couleur courante du fond.
 *	\param	couleur	La nouvelle couleur de fond.
 */
void ChangerCouleurFond(int couleur){
	printf("\033[%dm",couleur+10);
}

/**
 *	\fn		void ReinitialiserCouleur()
 *	\brief	Réinitalise les couleurs de texte et de fond.
 */
void ReinitialiserCouleur(){
	printf("\033[%dm",0);
}

/**
 *	\fn		void SePositionner(unsigned int x, unsigned int y)
 *	\brief	Se positionne dans la console.
 *	\param	x	L'abscisse du curseur.
 *	\param	y	L'ordonnée du curseur.
 */
void SePositionner(unsigned int x, unsigned int y){
	printf("\033[%u;%uH", y, x);
}

/**
 *	\fn		int RecupererAppuiTouche()
 *	\brief	Récupère le prochain appui de touche.
 *	\return	Un entier correspondant à la touche.
 *	\see	ToucheClavier
 */
int RecupererAppuiTouche(){
	int c = fgetc(stdin);
	switch (c)
	{
		/* Caractères non imprimables. */
		case 9  : return TOUCHE_TABULATION_HORIZONTALE;
		case 13 : return TOUCHE_ENTREE;
		//case 27 : return TOUCHE_ECHAP;
		case 32 : return TOUCHE_ESPACE;
		case 127 : return TOUCHE_RETOUR_ARRIERE;
		/* Caractères spéciaux. */
		case 33 : return TOUCHE_EXCLAMATION;
		case 34 : return TOUCHE_GUILLEMETS;
		case 35 : return TOUCHE_DIESE;
		case 36 : return TOUCHE_DOLLAR;
		case 37 : return TOUCHE_POURCENTAGE;
		case 38 : return TOUCHE_ESPERLUETTE;
		case 39 : return TOUCHE_APOSTROPHE;
		case 40 : return TOUCHE_PARENTHESE_GAUCHE;
		case 41 : return TOUCHE_PARENTHESE_DROITE;
		case 42 : return TOUCHE_ASTERISQUE;
		case 43 : return TOUCHE_PLUS;
		case 44 : return TOUCHE_VIRGULE;
		case 45 : return TOUCHE_MOINS;
		case 46 : return TOUCHE_POINT;
		case 47 : return TOUCHE_SLASH;
		case 58 : return TOUCHE_DOUBLE_POINTS;
		case 59 : return TOUCHE_POINT_VIRGULE;
		case 60 : return TOUCHE_CHEVRON_GAUCHE;
		case 61 : return TOUCHE_EGAL;
		case 62 : return TOUCHE_CHEVRON_DROIT;
		case 63 : return TOUCHE_INTERROGATION;
		case 64 : return TOUCHE_AROBASE;
		case 91 : return TOUCHE_CROCHET_GAUCHE;
		case 92 : return TOUCHE_ANTISLASH;
		case 93 : return TOUCHE_CROCHET_DROIT;
		case 94 : return TOUCHE_ACCENT_CIRCONFLEXE;
		case 95 : return TOUCHE_UNDERSCORE;
		case 96 : return TOUCHE_ACCENT_GRAVE;
		case 123 : return TOUCHE_ACCOLADE_GAUCHE;
		case 124 : return TOUCHE_BARRE_VERTICALE;
		case 125 : return TOUCHE_ACCOLADE_DROITE;
		case 126 : return TOUCHE_TILDE;
		/* Chiffres */
		case 48 : return TOUCHE_ZERO;
		case 49 : return TOUCHE_UN;
		case 50 : return TOUCHE_DEUX;
		case 51 : return TOUCHE_TROIS;
		case 52 : return TOUCHE_QUATRE;
		case 53 : return TOUCHE_CINQ;
		case 54 : return TOUCHE_SIX;
		case 55 : return TOUCHE_SEPT;
		case 56 : return TOUCHE_HUIT;
		case 57 : return TOUCHE_NEUF;
		/* Lettres majuscules. */
		case 65 : return TOUCHE_A_MAJ;
		case 66 : return TOUCHE_B_MAJ;
		case 67 : return TOUCHE_C_MAJ;
		case 68 : return TOUCHE_D_MAJ;
		case 69 : return TOUCHE_E_MAJ;
		case 70 : return TOUCHE_F_MAJ;
		case 71 : return TOUCHE_G_MAJ;
		case 72 : return TOUCHE_H_MAJ;
		case 73 : return TOUCHE_I_MAJ;
		case 74 : return TOUCHE_J_MAJ;
		case 75 : return TOUCHE_K_MAJ;
		case 76 : return TOUCHE_L_MAJ;
		case 77 : return TOUCHE_M_MAJ;
		case 78 : return TOUCHE_N_MAJ;
		case 79 : return TOUCHE_O_MAJ;
		case 80 : return TOUCHE_P_MAJ;
		case 81 : return TOUCHE_Q_MAJ;
		case 82 : return TOUCHE_R_MAJ;
		case 83 : return TOUCHE_S_MAJ;
		case 84 : return TOUCHE_T_MAJ;
		case 85 : return TOUCHE_U_MAJ;
		case 86 : return TOUCHE_V_MAJ;
		case 87 : return TOUCHE_W_MAJ;
		case 88 : return TOUCHE_X_MAJ;
		case 89 : return TOUCHE_Y_MAJ;
		case 90 : return TOUCHE_Z_MAJ;
		/* Lettres minuscules. */
		case 97 : return TOUCHE_A_MIN;
		case 98 : return TOUCHE_B_MIN;
		case 99 : return TOUCHE_C_MIN;
		case 100 : return TOUCHE_D_MIN;
		case 101 : return TOUCHE_E_MIN;
		case 102 : return TOUCHE_F_MIN;
		case 103 : return TOUCHE_G_MIN;
		case 104 : return TOUCHE_H_MIN;
		case 105 : return TOUCHE_I_MIN;
		case 106 : return TOUCHE_J_MIN;
		case 107 : return TOUCHE_K_MIN;
		case 108 : return TOUCHE_L_MIN;
		case 109 : return TOUCHE_M_MIN;
		case 110 : return TOUCHE_N_MIN;
		case 111 : return TOUCHE_O_MIN;
		case 112 : return TOUCHE_P_MIN;
		case 113 : return TOUCHE_Q_MIN;
		case 114 : return TOUCHE_R_MIN;
		case 115 : return TOUCHE_S_MIN;
		case 116 : return TOUCHE_T_MIN;
		case 117 : return TOUCHE_U_MIN;
		case 118 : return TOUCHE_V_MIN;
		case 119 : return TOUCHE_W_MIN;
		case 120 : return TOUCHE_X_MIN;
		case 121 : return TOUCHE_Y_MIN;
		case 122 : return TOUCHE_Z_MIN;
		/* Touches vraiment spéciales. */
		case 27 :
		{
			c = fgetc(stdin);
			switch (c)
			{
				case 91 : 
				{
					c = fgetc(stdin);
					switch (c)
					{
						case 49 : 
						{
							c = fgetc(stdin);
							switch (c)
							{
								case 55 :
								{
									c = fgetc(stdin);
									switch (c)
									{
										case 126 : return TOUCHE_F6;
									}
									break;
								}
								case 56 :
								{
									c = fgetc(stdin);
									switch (c)
									{
										case 126 : return TOUCHE_F7;
									}
									break;
								}
								case 57 :
								{
									c = fgetc(stdin);
									switch (c)
									{
										case 126 : return TOUCHE_F8;
									}
									break;
								}
								case 126 : return TOUCHE_ORIGINE;
							}
							break;
						}
						case 50 : 
						{
							c = fgetc(stdin);
							switch (c)
							{
								case 48 :
								{
									c = fgetc(stdin);
									switch (c)
									{
										case 126 : return TOUCHE_F9;
									}
									break;
								}
								case 49 :
								{
									c = fgetc(stdin);
									switch (c)
									{
										case 126 : return TOUCHE_F10;
									}
									break;
								}
								case 51 :
								{
									c = fgetc(stdin);
									switch (c)
									{
										case 126 : return TOUCHE_F11;
									}
									break;
								}
								case 52 :
								{
									c = fgetc(stdin);
									switch (c)
									{
										case 126 : return TOUCHE_F12;
									}
									break;
								}
								case 126 : return TOUCHE_INSERTION;
							}
							break;
						}
						case 51 :
						{
							c = fgetc(stdin);
							switch (c)
							{
								case 126 : return TOUCHE_ECHAP;
							}
							break;
						}
						case 52 :
						{
							c = fgetc(stdin);
							switch (c)
							{
								case 126 : return TOUCHE_FIN; 
							}
							break;
						}
						case 53 :
						{
							c = fgetc(stdin);
							switch (c)
							{
								case 126 : return TOUCHE_PAGE_PRECEDENTE; 
							}
							break;
						}
						case 54 :
						{
							c = fgetc(stdin);
							switch (c)
							{
								case 126 : return TOUCHE_PAGE_SUIVANTE; 
							}
							break;
						}
						case 65 : return TOUCHE_FLECHE_HAUT;
						case 66 : return TOUCHE_FLECHE_BAS;
						case 67 : return TOUCHE_FLECHE_DROITE;
						case 68 : return TOUCHE_FLECHE_GAUCHE;
						case 71 : return TOUCHE_CINQ_PAVE_NUMERIQUE;
						case 91 : 
						{
							c = fgetc(stdin);
							switch (c)
							{
								case 65 : return TOUCHE_F1;
								case 66 : return TOUCHE_F2;
								case 67 : return TOUCHE_F3;
								case 68 : return TOUCHE_F4;
								case 69 : return TOUCHE_F5;
							}
							break;
						}
						case 94 : return TOUCHE_ECHAP;
					}
					break;
				}
			}
			break;
		}
		case 194 : 
		{
			c = fgetc(stdin);
			switch (c)
			{
				case 163 : return TOUCHE_LIVRE;
				case 164 : return TOUCHE_DEVISE_GENERIQUE;
				case 167 : return TOUCHE_SECTION;
				case 168 : return TOUCHE_ACCENT_TREMA;
				case 176 : return TOUCHE_ACCENT_ROND;
				case 178 : return TOUCHE_PUISSANCE_DEUX;
			}
			break;
		}
		case 195 : 
		{
			c = fgetc(stdin);
			switch (c)
			{
				case 160 : return TOUCHE_A_MIN_GRAVE;
				case 161 : return TOUCHE_A_MIN_AIGU;
				case 162 : return TOUCHE_A_MIN_CIRCONFLEXE;
				case 163 : return TOUCHE_A_MIN_TILDE;
				case 164 : return TOUCHE_A_MIN_TREMA;
				case 165 : return TOUCHE_A_MIN_ROND;
				case 166 : return TOUCHE_AE_MIN;
				case 167 : return TOUCHE_C_CEDILLE;
				case 168 : return TOUCHE_E_MIN_GRAVE;
				case 169 : return TOUCHE_E_MIN_AIGU;
				case 170 : return TOUCHE_E_MIN_CIRCONFLEXE;
				case 171 : return TOUCHE_E_MIN_TREMA;
				case 172 : return TOUCHE_I_MIN_GRAVE;
				case 173 : return TOUCHE_I_MIN_AIGU;
				case 174 : return TOUCHE_I_MIN_CIRCONFLEXE;
				case 175 : return TOUCHE_I_MIN_TREMA;
				case 176 : return TOUCHE_ED_MIN;
				case 177 : return TOUCHE_N_MIN_TILDE;
				case 178 : return TOUCHE_O_MIN_GRAVE;
				case 179 : return TOUCHE_O_MIN_AIGU;
				case 180 : return TOUCHE_O_MIN_CIRCONFLEXE;
				case 181 : return TOUCHE_O_MIN_TILDE;
				case 182 : return TOUCHE_O_MIN_TREMA;
				case 183 : return TOUCHE_DIVISION;
				case 184 : return TOUCHE_O_BARRE;
				case 185 : return TOUCHE_U_MIN_GRAVE;
				case 186 : return TOUCHE_U_MIN_AIGU;
				case 187 : return TOUCHE_U_MIN_CIRCONFLEXE;
				case 188 : return TOUCHE_U_MIN_TREMA;
				case 189 : return TOUCHE_Y_MIN_AIGU;
				case 190 : return TOUCHE_THORN_MIN;
				case 191 : return TOUCHE_Y_MIN_TREMA;
			}
			break;
		}
		case 226 : 
		{
			c = fgetc(stdin);
			switch (c)
			{
				case 130 : 
				{
					c = fgetc(stdin);
					switch (c)
					{
						case 172 : return TOUCHE_EURO;
					}
					break;
				}
			}
			break;
		}
		case 233 : 
		{
			c = fgetc(stdin);
			switch (c)
			{
				case 133 : 
				{
					c = fgetc(stdin);
					switch (c)
					{
						case 146 : return TOUCHE_KANJI_JAPONAIS_SAKE;
					}
					break;
				}
				case 173 : 
				{
					c = fgetc(stdin);
					switch (c)
					{
						case 154 : return TOUCHE_KANJI_JAPONAIS_SAKANA;
					}
					break;
				}
			}
			break;
		}
	}
	return TOUCHE_INCONNUE;
}

void menu_echap(Menu* menu, Personnage* heros, 
char descn[NBR_DE_NOTES][MAX_DESC_NOTE], 
char desco[NBR_D_OBJETS][MAX_DESC_OBJET], 
char desci[NBR_INSTRU][MAX_DESC_INSTRU]){
	// On initialise les variables de cheminement
	int notOuObj = -1;
	int ss_menu_edit = -1;

	int nPartChoisie = -1;
	int nInvChoisie = -1;
	int objChoisi = -1;

	int opNPart = -1; // 2:3:4:6:RUN ENLEVER-MONTER-DESCENDRE-TOUT ENLEVER
	int opNInv = -1;
	int opObj = -1; // 1:RUN UTILISATION

	int qte = -1;
	int choixPart = -1; // 1:2:3:RUN DEPLACEMENT
	int confirm = -1; // 2:RUN SUPPRESSION
	
	int touche;
	int nbrN;
	int Nieme;

	// On demande à présent à l'utilisateur d'appuyer sur une touche.
	while (1==1){
		switch(menu->noteOuObjet){
			case -1 : // CHOIX DU MENU (EDITEUR OU OBJETS)
				if (notOuObj == -1) notOuObj = 1;
				// On récupère l'identifiant de la touche.
				do{
					EffacerEcran();
					afficher_menu_courant(menu, notOuObj, heros, descn, desco, desci);
					touche = RecupererAppuiTouche();
					switch (touche){
						case TOUCHE_FLECHE_HAUT :
						case TOUCHE_Z_MIN :
							notOuObj--;
							notOuObj = controle_selection(1, 4, notOuObj);
							break;

						case TOUCHE_FLECHE_BAS :
						case TOUCHE_S_MIN :
							notOuObj++;
							notOuObj = controle_selection(1, 4, notOuObj);
							break;

						case TOUCHE_ENTREE :
							menu->noteOuObjet = notOuObj;
							break;

						case TOUCHE_TABULATION_HORIZONTALE :
							initialiserMenu(menu);
							return;
					}
				}
				while (menu->noteOuObjet == -1);
				break;

			case 1 : // EDITEUR DE PARTITIONS
				switch(menu->sous_menu_editeur){
					case -1 : // CHOIX DE LA PARTITION OU DES NOTES LIBRES
						if (ss_menu_edit == -1) ss_menu_edit = 1;
						// On récupère l'identifiant de la touche.
						do{
							EffacerEcran();
							afficher_menu_courant(menu, ss_menu_edit, heros, descn, desco, desci);
							touche = RecupererAppuiTouche();
							switch (touche){
								case TOUCHE_FLECHE_HAUT :
								case TOUCHE_Z_MIN :
									ss_menu_edit--;
									ss_menu_edit = controle_selection(1, 4, ss_menu_edit);
									break;

								case TOUCHE_FLECHE_BAS :
								case TOUCHE_S_MIN :
									ss_menu_edit++;
									ss_menu_edit = controle_selection(1, 4, ss_menu_edit);
									break;

								case TOUCHE_ENTREE :
									menu->sous_menu_editeur = ss_menu_edit;
									break;

								case TOUCHE_RETOUR_ARRIERE :
									menu->noteOuObjet = -1;
									break;

								case TOUCHE_TABULATION_HORIZONTALE :
									initialiserMenu(menu);
									return;
							}
						}
						while (menu->sous_menu_editeur == -1 && menu->noteOuObjet != -1);
						break;

					case 1 : // BOLERO
					case 2 : // HYMNE
					case 3 : // SERENADE
						if (menu->notePartChoisie == -1){ // CHOIX DE LA NOTE
							if (nPartChoisie == -1) nPartChoisie = 0;
							// On récupère l'identifiant de la touche.
							do{
								EffacerEcran();
								afficher_menu_courant(menu, nPartChoisie, heros, descn, desco, desci);
								touche = RecupererAppuiTouche();
								switch (touche){
									case TOUCHE_FLECHE_HAUT :
									case TOUCHE_Z_MIN :
										nPartChoisie--;
										nPartChoisie = controle_selection(0, 49, nPartChoisie);
										break;

									case TOUCHE_FLECHE_BAS :
									case TOUCHE_S_MIN :
										nPartChoisie++;
										nPartChoisie = controle_selection(0, 49, nPartChoisie);
										break;

									case TOUCHE_FLECHE_GAUCHE :
									case TOUCHE_Q_MIN :
										nPartChoisie-=25;
										nPartChoisie = controle_selection(0, 49, nPartChoisie);
										break;

									case TOUCHE_FLECHE_DROITE :
									case TOUCHE_D_MIN :
										nPartChoisie+=25;
										nPartChoisie = controle_selection(0, 49, nPartChoisie);
										break;
										
									case TOUCHE_PLUS :
										menu->notePartChoisie = nPartChoisie;
										menu->opNotePart = 3;
										break;
										
									case TOUCHE_MOINS :
										menu->notePartChoisie = nPartChoisie;
										menu->opNotePart = 4;
										break;
										
									case TOUCHE_POINT :
										menu->notePartChoisie = nPartChoisie;
										menu->opNotePart = 5;
										break;
										
									case TOUCHE_E_MIN : 
										menu->notePartChoisie = nPartChoisie;
										menu->opNotePart = 2;
										break;
										
									case TOUCHE_E_MAJ :
										menu->notePartChoisie = nPartChoisie;
										menu->opNotePart = 6;
										break;
										
									case TOUCHE_CHEVRON_GAUCHE :
										menu->notePartChoisie = nPartChoisie;
										menu->opNotePart = 1;
										menu->choixPartition = 1;
										break;
										
									case TOUCHE_CHEVRON_DROIT :
										menu->notePartChoisie = nPartChoisie;
										menu->opNotePart = 1;
										menu->choixPartition = 2;
										break;

									case TOUCHE_ENTREE :
										menu->notePartChoisie = nPartChoisie;
										break;

									case TOUCHE_RETOUR_ARRIERE :
										menu->sous_menu_editeur = -1;
										nPartChoisie = -1;
										break;

									case TOUCHE_TABULATION_HORIZONTALE :
										initialiserMenu(menu);
										return;
								}
							}
							while (menu->notePartChoisie == -1 && menu->sous_menu_editeur != -1);
						}
						else if (menu->notePartChoisie >= 0 && menu->notePartChoisie < 50){ // NOTE CHOISIE
							switch(menu->opNotePart){
								case -1 : // CHOIX DE L'OPERATION A EFFECTUER SUR LA NOTE
									if (opNPart == -1) opNPart = 1;
									// On récupère l'identifiant de la touche.
									do{
										afficher_menu_courant(menu, opNPart, heros, descn, desco, desci);
										touche = RecupererAppuiTouche();
										switch (touche){
											case TOUCHE_FLECHE_HAUT :
											case TOUCHE_Z_MIN :
												opNPart--;
												opNPart = controle_selection(1, 5, opNPart);
												break;

											case TOUCHE_FLECHE_BAS :
											case TOUCHE_S_MIN :
												opNPart++;
												opNPart = controle_selection(1, 5, opNPart);
												break;

											case TOUCHE_ENTREE :
												menu->opNotePart = opNPart;
												break;

											case TOUCHE_RETOUR_ARRIERE :
												menu->notePartChoisie = -1;
												opNPart = -1;
												break;

											case TOUCHE_TABULATION_HORIZONTALE :
												initialiserMenu(menu);
												return;
										}
									}
									while (menu->opNotePart == -1 && menu->notePartChoisie != -1);
									break;

								case 1 : // DEPLACER
									switch(menu->choixPartition){
										case -1 : // CHOIX DE LA PARTITION DANS LAQUELLE DEPLACER
											if (choixPart == -1) choixPart = 1;
											// On récupère l'identifiant de la touche.
											do{
												afficher_menu_courant(menu, choixPart, heros, descn, desco, desci);
												touche = RecupererAppuiTouche();
												switch (touche){
													case TOUCHE_FLECHE_HAUT :
													case TOUCHE_Z_MIN :
														choixPart--;
														choixPart = controle_selection(1, 2, choixPart);
														break;

													case TOUCHE_FLECHE_BAS :
													case TOUCHE_S_MIN :
														choixPart++;
														choixPart = controle_selection(1, 2, choixPart);
														break;

													case TOUCHE_ENTREE :
														menu->choixPartition = choixPart;
														break;

													case TOUCHE_RETOUR_ARRIERE :
														menu->opNotePart = -1;
														break;

													case TOUCHE_TABULATION_HORIZONTALE :
														initialiserMenu(menu);
														return;
												}
											}
											while (menu->choixPartition == -1 && menu->opNotePart != -1);
											break;

										case 1 : // VERS PART PREC (SERENADE)
											switch (menu->sous_menu_editeur){
												case 1 : 
													deplacerNotePart(menu->notePartChoisie, heros->inventaire->Bolero, heros->inventaire->Serenade);
													break;
												
												case 2 :
													deplacerNotePart(menu->notePartChoisie, heros->inventaire->Hymne, heros->inventaire->Bolero);
													break;
													
												case 3 :
													deplacerNotePart(menu->notePartChoisie, heros->inventaire->Serenade, heros->inventaire->Hymne);
													break;
											}
											menu->choixPartition = choixPart = -1;
											menu->opNotePart = opNPart = -1;
											menu->notePartChoisie = -1;
											break;

										case 2 : // VERS PART SUIV (HYMNE)
											switch (menu->sous_menu_editeur){
												case 1 : 
													deplacerNotePart(menu->notePartChoisie, heros->inventaire->Bolero, heros->inventaire->Hymne);
													break;
												
												case 2 :
													deplacerNotePart(menu->notePartChoisie, heros->inventaire->Hymne, heros->inventaire->Serenade);
													break;
													
												case 3 :
													deplacerNotePart(menu->notePartChoisie, heros->inventaire->Serenade, heros->inventaire->Bolero);
													break;
											}
											menu->choixPartition = choixPart = -1;
											menu->opNotePart = opNPart = -1;
											menu->notePartChoisie = -1;
											break;
									}
									break;

								case 2 : // ENLEVER
									switch (menu->sous_menu_editeur){
										case 1 : 
											enleverNote(menu->notePartChoisie, heros->inventaire->Bolero, heros->inventaire->contenuNot);
											break;
										
										case 2 :
											enleverNote(menu->notePartChoisie, heros->inventaire->Hymne, heros->inventaire->contenuNot);
											break;
											
										case 3 :
											enleverNote(menu->notePartChoisie, heros->inventaire->Serenade, heros->inventaire->contenuNot);
											break;
									}
									menu->opNotePart = opNPart = -1;
									menu->notePartChoisie = -1;
									break;

								case 3 : // MONTER
									switch (menu->sous_menu_editeur){
										case 1 : 
											if (monterNote(menu->notePartChoisie, heros->inventaire->Bolero) == 0){;
											nPartChoisie--;
										}
											break;
										
										case 2 :
											if (monterNote(menu->notePartChoisie, heros->inventaire->Hymne) == 0){;
											nPartChoisie--;
										}
											break;
											
										case 3 :
											if (monterNote(menu->notePartChoisie, heros->inventaire->Serenade) == 0){;
											nPartChoisie--;
										}
											break;
									}
									menu->opNotePart = opNPart = -1;
									menu->notePartChoisie = -1;
									break;

								case 4 : //DESCENDRE
									switch (menu->sous_menu_editeur){
										case 1 : 
											if (descendreNote(menu->notePartChoisie, heros->inventaire->Bolero) == 0){;
											nPartChoisie++;
										}
											break;
										
										case 2 :
											if (descendreNote(menu->notePartChoisie, heros->inventaire->Hymne) == 0){;
											nPartChoisie++;
										}
											break;
											
										case 3 :
											if (descendreNote(menu->notePartChoisie, heros->inventaire->Serenade) == 0){;
											nPartChoisie++;
										}
											break;
									}
									menu->opNotePart = opNPart = -1;
									menu->notePartChoisie = -1;
									break;

								case 5 : // JETER
									switch(menu->confirmation){
										case -1 :
											confirm = 1;
											// On récupère l'identifiant de la touche.
											do{
												afficher_menu_courant(menu, confirm, heros, descn, desco, desci);
												touche = RecupererAppuiTouche();
												switch (touche){
													case TOUCHE_FLECHE_HAUT :
													case TOUCHE_Z_MIN :
														confirm--;
														confirm = controle_selection(1, 2, confirm);
														break;

													case TOUCHE_FLECHE_BAS :
													case TOUCHE_S_MIN :
														confirm++;
														confirm = controle_selection(1, 2, confirm);
														break;
														
													case TOUCHE_O_MIN :
														menu->confirmation = 2;
														break;

													case TOUCHE_N_MIN :
														menu->confirmation = 1;
														break;

													case TOUCHE_ENTREE :
														menu->confirmation = confirm;
														break;

													case TOUCHE_RETOUR_ARRIERE :
														menu->opNotePart = -1;
														break;

													case TOUCHE_TABULATION_HORIZONTALE :
														initialiserMenu(menu);
														return;
												}
											}
											while (menu->confirmation == -1 && menu->opNotePart != -1);
											break;

										case 1 :
											menu->confirmation = -1;
											menu->opNotePart = -1;
											opNPart = -1;
											menu->notePartChoisie = -1;
											break;

										case 2 :
											switch (menu->sous_menu_editeur){
												case 1 : 
													jeterNotePart(menu->notePartChoisie, heros->inventaire->Bolero, heros->inventaire->contenuNot);
													break;
												
												case 2 :
													jeterNotePart(menu->notePartChoisie, heros->inventaire->Hymne, heros->inventaire->contenuNot);
													break;
													
												case 3 :
													jeterNotePart(menu->notePartChoisie, heros->inventaire->Serenade, heros->inventaire->contenuNot);
													break;
											}
											menu->confirmation = -1;
											menu->opNotePart = -1;
											opNPart = -1;
											menu->notePartChoisie = -1;
											break;
									}
									break;
									
								case 6 : // TOUT ENLEVER
									switch (menu->sous_menu_editeur){
										case 1 :
											for (menu->notePartChoisie = 0; menu->notePartChoisie < 50; menu->notePartChoisie++){
												enleverNote(menu->notePartChoisie, heros->inventaire->Bolero, heros->inventaire->contenuNot);
											}
											break;
										
										case 2 :
											for (menu->notePartChoisie = 0; menu->notePartChoisie < 50; menu->notePartChoisie++){
												enleverNote(menu->notePartChoisie, heros->inventaire->Hymne, heros->inventaire->contenuNot);
											}
											break;
											
										case 3 :
											for (menu->notePartChoisie = 0; menu->notePartChoisie < 50; menu->notePartChoisie++){
												enleverNote(menu->notePartChoisie, heros->inventaire->Serenade, heros->inventaire->contenuNot);
											}
											break;
									}
									menu->opNotePart = opNPart = -1;
									menu->notePartChoisie = -1;
									break;
							}
						}
						break;

					case 4 : // NOTES D'INVENTAIRE
						if (menu->noteInvChoisie == -1){ // CHOIX DE LA NOTE
							if (nInvChoisie == -1) nInvChoisie = 0;
							// On récupère l'identifiant de la touche.
							do{
								nbrN = nombreNotesDiff(heros->inventaire->contenuNot);
								EffacerEcran();
								afficher_menu_courant(menu, nInvChoisie, heros, descn, desco, desci);
								touche = RecupererAppuiTouche();
								switch (touche){
									case TOUCHE_FLECHE_HAUT :
									case TOUCHE_Z_MIN :
										nInvChoisie--;
										nInvChoisie = controle_selection(0, nbrN-1, nInvChoisie);
										break;

									case TOUCHE_FLECHE_BAS :
									case TOUCHE_S_MIN :
										nInvChoisie++;
										nInvChoisie = controle_selection(0, nbrN-1, nInvChoisie);
										break;

									case TOUCHE_FLECHE_GAUCHE :
									case TOUCHE_Q_MIN :
										nInvChoisie-=(nbrN/5);
										nInvChoisie = controle_selection(0, nbrN-1, nInvChoisie);
										break;

									case TOUCHE_FLECHE_DROITE :
									case TOUCHE_D_MIN :
										nInvChoisie+=(nbrN/5);
										nInvChoisie = controle_selection(0, nbrN-1, nInvChoisie);
										break;

									case TOUCHE_ENTREE :
										if (nbrN > 0) menu->noteInvChoisie = nInvChoisie;
										else{
											menu->sous_menu_editeur = -1;
											nInvChoisie = -1;
										}
										break;

									case TOUCHE_RETOUR_ARRIERE :
										menu->sous_menu_editeur = -1;
										nInvChoisie = -1;
										break;

									case TOUCHE_TABULATION_HORIZONTALE :
										initialiserMenu(menu);
										return;
								}
							}
							while (menu->noteInvChoisie == -1 && menu->sous_menu_editeur != -1);
						}
						else if ((menu->noteInvChoisie >= 0) && (menu->noteInvChoisie < nombreNotesDiff(heros->inventaire->contenuNot))){
							switch(menu->opNoteInv){
								case -1 : // CHOIX DE L'OPERATION A EFFECTUER SUR LA NOTE
									if (opNInv == -1) opNInv = 1;
									// On récupère l'identifiant de la touche.
									do{
										afficher_menu_courant(menu, opNInv, heros, descn, desco, desci);
										touche = RecupererAppuiTouche();
										switch (touche){
											case TOUCHE_FLECHE_HAUT :
											case TOUCHE_Z_MIN :
												opNInv--;
												opNInv = controle_selection(1, 2, opNInv);
												break;

											case TOUCHE_FLECHE_BAS :
											case TOUCHE_S_MIN :
												opNInv++;
												opNInv = controle_selection(1, 2, opNInv);
												break;

											case TOUCHE_ENTREE :
												menu->opNoteInv = opNInv;
												break;

											case TOUCHE_RETOUR_ARRIERE :
												menu->noteInvChoisie = -1;
												opNInv = -1;
												break;

											case TOUCHE_TABULATION_HORIZONTALE :
												initialiserMenu(menu);
												return;
										}
									}
									while (menu->opNoteInv == -1 && menu->noteInvChoisie != -1);
									break;

								case 1 : // DEPLACER
									Nieme = niemeNoteNonVide(nInvChoisie, heros->inventaire->contenuNot);
									if (menu->quantite == -1){
										qte = 1;
										// On récupère l'identifiant de la touche.
										do{
											afficher_menu_courant(menu, qte, heros, descn, desco, desci);
											touche = RecupererAppuiTouche();
											switch (touche){
												case TOUCHE_FLECHE_HAUT :
												case TOUCHE_Z_MIN :
													qte++;
													qte = controle_selection(1, heros->inventaire->contenuNot[Nieme].quantite[1], qte);
													break;

												case TOUCHE_FLECHE_BAS :
												case TOUCHE_S_MIN :
													qte--;
													qte = controle_selection(1, heros->inventaire->contenuNot[Nieme].quantite[1], qte);
													break;
													
												case TOUCHE_UN :
													qte = 1;
													break;
													
												case TOUCHE_DEUX :
													qte = 2;
													qte = controle_selection(1, heros->inventaire->contenuNot[Nieme].quantite[1], qte);
													break;
													
												case TOUCHE_TROIS :
													qte = 3;
													qte = controle_selection(1, heros->inventaire->contenuNot[Nieme].quantite[1], qte);
													break;
													
												case TOUCHE_QUATRE :
													qte = 4;
													qte = controle_selection(1, heros->inventaire->contenuNot[Nieme].quantite[1], qte);
													break;
													
												case TOUCHE_CINQ :
													qte = 5;
													qte = controle_selection(1, heros->inventaire->contenuNot[Nieme].quantite[1], qte);
													break;
													
												case TOUCHE_SIX :
													qte = 6;
													qte = controle_selection(1, heros->inventaire->contenuNot[Nieme].quantite[1], qte);
													break;
													
												case TOUCHE_SEPT :
													qte = 7;
													qte = controle_selection(1, heros->inventaire->contenuNot[Nieme].quantite[1], qte);
													break;
													
												case TOUCHE_HUIT :
													qte = 8;
													qte = controle_selection(1, heros->inventaire->contenuNot[Nieme].quantite[1], qte);
													break;
													
												case TOUCHE_NEUF :
													qte = 9;
													qte = controle_selection(1, heros->inventaire->contenuNot[Nieme].quantite[1], qte);
													break;
													
												case TOUCHE_ENTREE :
													menu->quantite = qte;
													break;

												case TOUCHE_RETOUR_ARRIERE :
													menu->opNoteInv = -1;
													break;

												case TOUCHE_TABULATION_HORIZONTALE :
													initialiserMenu(menu);
													return;
											}
										}
										while (menu->quantite == -1 && menu->opNoteInv != -1);
									}
									else if ((menu->quantite > 0) && (menu->quantite <= heros->inventaire->contenuNot[Nieme].quantite[1])){
										switch(menu->choixPartition){
											case -1 : // CHOIX DE LA PARTITION DANS LAQUELLE DEPLACER
												if (choixPart == -1) choixPart = 1;
												// On récupère l'identifiant de la touche.
												do{
													afficher_menu_courant(menu, choixPart, heros, descn, desco, desci);
													touche = RecupererAppuiTouche();
													switch (touche){
														case TOUCHE_FLECHE_HAUT :
														case TOUCHE_Z_MIN :
															choixPart--;
															choixPart = controle_selection(1, 3, choixPart);
															break;
	
														case TOUCHE_FLECHE_BAS :
														case TOUCHE_S_MIN :
															choixPart++;
															choixPart = controle_selection(1, 3, choixPart);
															break;
															
														case TOUCHE_ENTREE :
															menu->choixPartition = choixPart;
															break;
	
														case TOUCHE_RETOUR_ARRIERE :
															menu->quantite = -1;
															menu->opNoteInv = -1;
															break;
	
														case TOUCHE_TABULATION_HORIZONTALE :
															initialiserMenu(menu);
															return;
													}
												}
												while (menu->choixPartition == -1 && menu->opNoteInv != -1);
												break;

											case 1 : // VERS LE BOLERO
												// appliquer déplacement d'une note d'inventaire vers le boléro
												while(menu->quantite != 0){
													deplacerNoteInv(heros->niveau, niemeNoteNonVide(nInvChoisie, heros->inventaire->contenuNot), heros->inventaire, heros->inventaire->Bolero);
													menu->quantite--;
												}
												menu->choixPartition = choixPart = -1;
												menu->quantite = -1;
												menu->opNoteInv = opNInv = -1;
												menu->noteInvChoisie = -1;
												nInvChoisie = controle_selection(0, nombreNotesDiff(heros->inventaire->contenuNot)-1, nInvChoisie);
												break;

											case 2 : // VERS L'HYMNE
												// appliquer déplacement d'une note d'inventaire vers l'hymne
												while(menu->quantite != 0){
													deplacerNoteInv(heros->niveau, niemeNoteNonVide(nInvChoisie, heros->inventaire->contenuNot), heros->inventaire, heros->inventaire->Hymne);
													menu->quantite--;
												}
												menu->choixPartition = choixPart = -1;
												menu->quantite = -1;
												menu->opNoteInv = opNInv = -1;
												menu->noteInvChoisie = -1;
												nInvChoisie = controle_selection(0, nombreNotesDiff(heros->inventaire->contenuNot)-1, nInvChoisie);
												break;

											case 3 : // VERS LA SERENADE
												// appliquer déplacement d'une note d'inventaire vers la sérénade
												while(menu->quantite != 0){
													deplacerNoteInv(heros->niveau, niemeNoteNonVide(nInvChoisie, heros->inventaire->contenuNot), heros->inventaire, heros->inventaire->Serenade);
													menu->quantite--;
												}
												menu->choixPartition = choixPart = -1;
												menu->quantite = -1;
												menu->opNoteInv = opNInv = -1;
												menu->noteInvChoisie = -1;
												nInvChoisie = controle_selection(0, nombreNotesDiff(heros->inventaire->contenuNot)-1, nInvChoisie);
												break;
										}
									}
									break;

								case 2 : // JETER
									Nieme = niemeNoteNonVide(nInvChoisie, heros->inventaire->contenuNot);
									if (menu->quantite == -1){
											qte = 1;
											// On récupère l'identifiant de la touche.
											do{
												afficher_menu_courant(menu, qte, heros, descn, desco, desci);
												touche = RecupererAppuiTouche();
												switch (touche){
													case TOUCHE_FLECHE_HAUT :
													case TOUCHE_Z_MIN :
														qte++;
														qte = controle_selection(1, heros->inventaire->contenuNot[Nieme].quantite[1], qte);
														break;

													case TOUCHE_FLECHE_BAS :
													case TOUCHE_S_MIN :
														qte--;
														qte = controle_selection(1, heros->inventaire->contenuNot[Nieme].quantite[1], qte);
														break;
														
													case TOUCHE_UN :
														qte = 1;
														break;
														
													case TOUCHE_DEUX :
														qte = 2;
														qte = controle_selection(1, heros->inventaire->contenuNot[Nieme].quantite[1], qte);
														break;
														
													case TOUCHE_TROIS :
														qte = 3;
														qte = controle_selection(1, heros->inventaire->contenuNot[Nieme].quantite[1], qte);
														break;
														
													case TOUCHE_QUATRE :
														qte = 4;
														qte = controle_selection(1, heros->inventaire->contenuNot[Nieme].quantite[1], qte);
														break;
														
													case TOUCHE_CINQ :
														qte = 5;
														qte = controle_selection(1, heros->inventaire->contenuNot[Nieme].quantite[1], qte);
														break;
														
													case TOUCHE_SIX :
														qte = 6;
														qte = controle_selection(1, heros->inventaire->contenuNot[Nieme].quantite[1], qte);
														break;
														
													case TOUCHE_SEPT :
														qte = 7;
														qte = controle_selection(1, heros->inventaire->contenuNot[Nieme].quantite[1], qte);
														break;
														
													case TOUCHE_HUIT :
														qte = 8;
														qte = controle_selection(1, heros->inventaire->contenuNot[Nieme].quantite[1], qte);
														break;
														
													case TOUCHE_NEUF :
														qte = 9;
														qte = controle_selection(1, heros->inventaire->contenuNot[Nieme].quantite[1], qte);
														break;
														
													case TOUCHE_ENTREE :
														menu->quantite = qte;
														break;

													case TOUCHE_RETOUR_ARRIERE :
														menu->opNoteInv = -1;
														break;

													case TOUCHE_TABULATION_HORIZONTALE :
														initialiserMenu(menu);
														return;
												}
											}
											while (menu->quantite == -1 && menu->opNoteInv != -1);
									}
									else if ((menu->quantite > 0) && (menu->quantite <= heros->inventaire->contenuNot[Nieme].quantite[1])){
										switch(menu->confirmation){
											case -1 :
												confirm = 1;
												// On récupère l'identifiant de la touche.
												do{
													afficher_menu_courant(menu, confirm, heros, descn, desco, desci);
													touche = RecupererAppuiTouche();
													switch (touche){
														case TOUCHE_FLECHE_HAUT :
														case TOUCHE_Z_MIN :
															confirm--;
															confirm = controle_selection(1, 2, confirm);
															break;

														case TOUCHE_FLECHE_BAS :
														case TOUCHE_S_MIN :
															confirm++;
															confirm = controle_selection(1, 2, confirm);
															break;
															
														case TOUCHE_O_MIN :
															menu->confirmation = 2;
															break;
	
														case TOUCHE_N_MIN :
															menu->confirmation = 1;
															break;
	
														case TOUCHE_ENTREE :
															menu->confirmation = confirm;
															break;

														case TOUCHE_RETOUR_ARRIERE :
															menu->quantite = -1;
															menu->opNoteInv = -1;
															break;

														case TOUCHE_TABULATION_HORIZONTALE :
															initialiserMenu(menu);
															return;
													}
												}
												while (menu->confirmation == -1 && menu->opNoteInv != -1);
												break;

											case 1 :
												menu->confirmation = -1;
												menu->quantite = -1;
												menu->opNoteInv = -1;
												opNInv = -1;
												menu->noteInvChoisie = -1;
												break;

											case 2 :
												jeterNoteInv(qte, niemeNoteNonVide(nInvChoisie, heros->inventaire->contenuNot), heros->inventaire->contenuNot);
												menu->confirmation = -1;
												menu->quantite = -1;
												menu->opNoteInv = -1;
												opNInv = -1;
												menu->noteInvChoisie = -1;
												nInvChoisie = controle_selection(0, nombreNotesDiff(heros->inventaire->contenuNot)-1, nInvChoisie);
												break;
										}
									}
									break;
							}
						}
						break;
				}
				break;

			case 2 : // OBJETS
				if (menu->objetChoisi == -1){ // CHOIX DE L'OBJET
					if (objChoisi == -1) objChoisi = 0;
					// On récupère l'identifiant de la touche.
					do{
						nbrN = nombreDobjets(heros->inventaire->contenuObj);
						EffacerEcran();
						afficher_menu_courant(menu, objChoisi, heros, descn, desco, desci);
						touche = RecupererAppuiTouche();
						switch (touche){
							case TOUCHE_FLECHE_HAUT :
							case TOUCHE_Z_MIN :
								objChoisi--;
								objChoisi = controle_selection(0, nbrN-1, objChoisi);
								break;

							case TOUCHE_FLECHE_BAS :
							case TOUCHE_S_MIN :
								objChoisi++;
								objChoisi = controle_selection(0, nbrN-1, objChoisi);
								break;
								
							case TOUCHE_U_MIN :
								menu->objetChoisi = objChoisi;
								menu->opObjet = 1;
								break;
								
							case TOUCHE_ENTREE :
								if (nbrN > 0) menu->objetChoisi = objChoisi;
								else {
									menu->noteOuObjet = -1;
									objChoisi = -1;
								}
								break;

							case TOUCHE_RETOUR_ARRIERE :
								menu->noteOuObjet = -1;
								objChoisi = -1;
								break;

							case TOUCHE_TABULATION_HORIZONTALE :
								initialiserMenu(menu);
								return;
						}
					}
					while (menu->objetChoisi == -1 && menu->noteOuObjet != -1);
				}
				else if (menu->objetChoisi >= 0 && menu->objetChoisi < nombreDobjets(heros->inventaire->contenuObj)){ // OBJET CHOISI
					switch(menu->opObjet){
						case -1 : // CHOIX DE L'OPERATION A EFFECTUER SUR L'OBJET
							if (opObj == -1) opObj = 1;
							// On récupère l'identifiant de la touche.
							do{
								afficher_menu_courant(menu, opObj, heros, descn, desco, desci);
								touche = RecupererAppuiTouche();
								switch (touche){
									case TOUCHE_FLECHE_HAUT :
									case TOUCHE_Z_MIN :
										opObj--;
										opObj = controle_selection(1, 2, opObj);
										break;

									case TOUCHE_FLECHE_BAS :
									case TOUCHE_S_MIN :
										opObj++;
										opObj = controle_selection(1, 2, opObj);
										break;

									case TOUCHE_ENTREE :
										menu->opObjet = opObj;
										break;

									case TOUCHE_RETOUR_ARRIERE :
										menu->objetChoisi = -1;
										break;

									case TOUCHE_TABULATION_HORIZONTALE :
										initialiserMenu(menu);
										return;
								}
							}
							while (menu->opObjet == -1 && menu->objetChoisi != -1);
							break;

						case 1 : // UTILISER
							Nieme = niemeObjetNonVide(objChoisi, heros->inventaire->contenuObj);
							utiliserObjet(Nieme, heros->inventaire->contenuObj, heros);
							menu->opObjet = opObj = -1;
							menu->objetChoisi = -1;
							objChoisi = controle_selection(0, nombreDobjets(heros->inventaire->contenuObj)-1, objChoisi);
							break;

						case 2 : // JETER
							Nieme = niemeObjetNonVide(objChoisi, heros->inventaire->contenuObj);
							if (menu->quantite == -1){
									qte = 1;
									// On récupère l'identifiant de la touche.
									do{
										afficher_menu_courant(menu, qte, heros, descn, desco, desci);
										touche = RecupererAppuiTouche();
										switch (touche){
											case TOUCHE_FLECHE_HAUT :
											case TOUCHE_Z_MIN :
												qte++;
												qte = controle_selection(1, heros->inventaire->contenuObj[Nieme].quantite, qte);
												break;

											case TOUCHE_FLECHE_BAS :
											case TOUCHE_S_MIN :
												qte--;
												qte = controle_selection(1, heros->inventaire->contenuObj[Nieme].quantite, qte);
												break;
												
											case TOUCHE_UN :
												qte = 1;
												break;
												
											case TOUCHE_DEUX :
												qte = 2;
												qte = controle_selection(1, heros->inventaire->contenuObj[Nieme].quantite, qte);
												break;
												
											case TOUCHE_TROIS :
												qte = 3;
												qte = controle_selection(1, heros->inventaire->contenuObj[Nieme].quantite, qte);
												break;
												
											case TOUCHE_QUATRE :
												qte = 4;
												qte = controle_selection(1, heros->inventaire->contenuObj[Nieme].quantite, qte);
												break;
												
											case TOUCHE_CINQ :
												qte = 5;
												qte = controle_selection(1, heros->inventaire->contenuObj[Nieme].quantite, qte);
												break;
												
											case TOUCHE_SIX :
												qte = 6;
												qte = controle_selection(1, heros->inventaire->contenuObj[Nieme].quantite, qte);
												break;
												
											case TOUCHE_SEPT :
												qte = 7;
												qte = controle_selection(1, heros->inventaire->contenuObj[Nieme].quantite, qte);
												break;
												
											case TOUCHE_HUIT :
												qte = 8;
												qte = controle_selection(1, heros->inventaire->contenuObj[Nieme].quantite, qte);
												break;
												
											case TOUCHE_NEUF :
												qte = 9;
												qte = controle_selection(1, heros->inventaire->contenuObj[Nieme].quantite, qte);
												break;

											case TOUCHE_ENTREE :
												menu->quantite = qte;
												break;

											case TOUCHE_RETOUR_ARRIERE :
												menu->opObjet = -1;
												break;

											case TOUCHE_TABULATION_HORIZONTALE :
												initialiserMenu(menu);
												return;
										}
									}
									while (menu->quantite == -1 && menu->opObjet != -1);
							}
							else if ((menu->quantite > 0) && (menu->quantite <= heros->inventaire->contenuObj[Nieme].quantite)){
								switch(menu->confirmation){
									case -1 :
										confirm = 1;
										// On récupère l'identifiant de la touche.
										do{
											afficher_menu_courant(menu, confirm, heros, descn, desco, desci);
											touche = RecupererAppuiTouche();
											switch (touche){
												case TOUCHE_FLECHE_HAUT :
												case TOUCHE_Z_MIN :
													confirm--;
													confirm = controle_selection(1, 2, confirm);
													break;

												case TOUCHE_FLECHE_BAS :
												case TOUCHE_S_MIN :
													confirm++;
													confirm = controle_selection(1, 2, confirm);
													break;

												case TOUCHE_O_MIN :
													menu->confirmation = 2;
													break;

												case TOUCHE_N_MIN :
													menu->confirmation = 1;
													break;

												case TOUCHE_ENTREE :
													menu->confirmation = confirm;
													break;

												case TOUCHE_RETOUR_ARRIERE :
													menu->opObjet = -1;
													break;

												case TOUCHE_TABULATION_HORIZONTALE :
													initialiserMenu(menu);
													return;
											}
										}
										while (menu->confirmation == -1 && menu->opObjet != -1);
										break;

									case 1 :
										menu->confirmation = -1;
										menu->quantite = -1;
										menu->opObjet = -1;
										opObj = -1;
										menu->objetChoisi = -1;
										break;

									case 2 :
										jeterObjet(qte, niemeObjetNonVide(objChoisi, heros->inventaire->contenuObj), heros->inventaire->contenuObj);
										menu->confirmation = -1;
										menu->quantite = -1;
										menu->opObjet = -1;
										opObj = -1;
										menu->objetChoisi = -1;
										objChoisi = controle_selection(0, nombreDobjets(heros->inventaire->contenuObj)-1, objChoisi);
										break;
								}
							}
							break;
					}
				}
				break;
				
			case 3 : // SAUVEGARDER ?
				return;
				
			case 4 : // QUITTER LE JEU
				return;
		}
	}
}

int controle_selection(int min, int max, int selection){
	if (selection < min) return min;
	else if (selection > max) return max;
	else return selection;
}

void initialiserMenu(Menu* menu){
	menu->noteOuObjet = -1;
	menu->sous_menu_editeur = -1;

	menu->notePartChoisie = -1;
	menu->noteInvChoisie = -1;
	menu->objetChoisi = -1;

	menu->opNotePart = -1;
	menu->opNoteInv = -1;
	menu->opObjet = -1;

	menu->quantite = -1;
	menu->choixPartition = -1;
	menu->confirmation = -1;
}

void afficher_menu_courant(Menu* menu, int num, Personnage* p, 
char descn[NBR_DE_NOTES][MAX_DESC_NOTE], 
char desco[NBR_D_OBJETS][MAX_DESC_OBJET], 
char desci[NBR_INSTRU][MAX_DESC_INSTRU]){
	int i, j;
	int nbrnotes, cinquieme;
	int nbrobjets;
	int Nieme;
	int potRestant;
	switch(menu->noteOuObjet){
		case -1 : // premier choix
			if (num == 1){
				printf("\n\r\t");
				ChangerCouleurTexte(COULEUR_BLEU);
				printf("Editeur de partitions");
				ChangerCouleurTexte(COULEUR_BLANC);
				printf("\n\r\tFouiller dans le sac");
				printf("\n\r\tSauvegarder");
				printf("\n\r\tQuitter le jeu");
			}
			else if (num == 2){
				printf("\n\r\tEditeur de partitions");
				ChangerCouleurTexte(COULEUR_BLEU);
				printf("\n\r\tFouiller dans le sac");
				ChangerCouleurTexte(COULEUR_BLANC);
				printf("\n\r\tSauvegarder");
				printf("\n\r\tQuitter le jeu");
			}
			else if (num == 3){
				printf("\n\r\tEditeur de partitions");
				printf("\n\r\tFouiller dans le sac");
				ChangerCouleurTexte(COULEUR_BLEU);
				printf("\n\r\tSauvegarder");
				ChangerCouleurTexte(COULEUR_BLANC);
				printf("\n\r\tQuitter le jeu");
			}
			else{
				printf("\n\r\tEditeur de partitions");
				printf("\n\r\tFouiller dans le sac");
				printf("\n\r\tSauvegarder");
				ChangerCouleurTexte(COULEUR_BLEU);
				printf("\n\r\tQuitter le jeu");
				ChangerCouleurTexte(COULEUR_BLANC);
			}
			break;
			
		case 1 : // éditeur
			switch(menu->sous_menu_editeur){
				case -1 : // choix de la partition ou des notes d'inventaire
					if (num == 1){
						ChangerCouleurTexte(COULEUR_BLEU);
						printf("\n\r\tBoléro");
						ChangerCouleurTexte(COULEUR_BLANC);
						printf("\n\r\tHymne\n\r\tSérénade\n\r\tRéserve");
					}
					else if (num == 2){
						printf("\n\r\tBoléro");
						ChangerCouleurTexte(COULEUR_BLEU);
						printf("\n\r\tHymne");
						ChangerCouleurTexte(COULEUR_BLANC);
						printf("\n\r\tSérénade\n\r\tRéserve");
					}
					else if (num == 3){
						printf("\n\r\tBoléro\n\r\tHymne");
						ChangerCouleurTexte(COULEUR_BLEU);
						printf("\n\r\tSérénade");
						ChangerCouleurTexte(COULEUR_BLANC);
						printf("\n\r\tRéserve");
					}
					else{
						printf("\n\r\tBoléro\n\r\tHymne\n\r\tSérénade");
						ChangerCouleurTexte(COULEUR_BLEU);
						printf("\n\r\tRéserve");
						ChangerCouleurTexte(COULEUR_BLANC);							
					}
					break;
					
				case 1 : // boléro
					potRestant = p->inventaire->Bolero->potentiel - calculPotentielPart(p->inventaire->Bolero);
					if (menu->notePartChoisie == -1){ // choix de la note
						for (i=0; i<25; i++){
							if (i == num){
								ChangerCouleurTexte(COULEUR_BLEU);
								if (p->inventaire->Bolero->contenu[i] != NULL){
									printf("\n\r %s", p->inventaire->Bolero->contenu[i]->nom);
								}
								else printf("\n\r - - - - ");
								ChangerCouleurTexte(COULEUR_BLANC);
							}
							else{
								if (p->inventaire->Bolero->contenu[i] != NULL){
									printf("\n\r %s", p->inventaire->Bolero->contenu[i]->nom);
								}
								else printf("\n\r - - - - ");
							}
						}
						for (i=25; i<50; i++){
							SePositionner(35, i-23);
							if (i == num){
								ChangerCouleurTexte(COULEUR_BLEU);
								if (p->inventaire->Bolero->contenu[i] != NULL){
									printf(" %s", p->inventaire->Bolero->contenu[i]->nom);
								}
								else printf(" - - - - ");
								ChangerCouleurTexte(COULEUR_BLANC);
							}
							else{
								if (p->inventaire->Bolero->contenu[i] != NULL){
									printf(" %s", p->inventaire->Bolero->contenu[i]->nom);
								}
								else printf(" - - - - ");
							}
						}
						
						SePositionner(0, 29);
						printf(">---------Potentiel restant : %d----------<", potRestant);
						if (p->inventaire->Bolero->contenu[num] != NULL){
							SePositionner(2, 32);
							printf("Niveau : %d\n\r ", p->inventaire->Bolero->contenu[num]->niveau);
							printf("Attaque : %d\n\r ", p->inventaire->Bolero->contenu[num]->attaque);
							printf("Défense : %d\n\r ", p->inventaire->Bolero->contenu[num]->defense);
							printf("Points de vie : %d", p->inventaire->Bolero->contenu[num]->pv);
							SePositionner(24, 32);
							for (i=0; i<80; i++) printf("%c", descn[p->inventaire->Bolero->contenu[num]->id][i]);
							while (descn[p->inventaire->Bolero->contenu[num]->id][i] != 32 && i<100){
								printf("%c", descn[p->inventaire->Bolero->contenu[num]->id][i]);
								i++;
							}
							SePositionner(24, 33);
							for (i=i+1; i<180; i++) printf("%c", descn[p->inventaire->Bolero->contenu[num]->id][i]);
							while (descn[p->inventaire->Bolero->contenu[num]->id][i] != 32 && i<200){
								printf("%c", descn[p->inventaire->Bolero->contenu[num]->id][i]);
								i++;
							}
							SePositionner(24, 34);
							for (i=i+1; i<280; i++) printf("%c", descn[p->inventaire->Bolero->contenu[num]->id][i]);
							while (descn[p->inventaire->Bolero->contenu[num]->id][i] != 32 && i<300){
								printf("%c", descn[p->inventaire->Bolero->contenu[num]->id][i]);
								i++;
							}
							SePositionner(24, 35);
							for (i=i+1; i<380; i++) printf("%c", descn[p->inventaire->Bolero->contenu[num]->id][i]);
							while (descn[p->inventaire->Bolero->contenu[num]->id][i] != 32 && i<400){
								printf("%c", descn[p->inventaire->Bolero->contenu[num]->id][i]);
								i++;
							}
							SePositionner(24, 36);
							for (i=i+1; i<480; i++) printf("%c", descn[p->inventaire->Bolero->contenu[num]->id][i]);
							while (descn[p->inventaire->Bolero->contenu[num]->id][i] != 32 && i<500){
								printf("%c", descn[p->inventaire->Bolero->contenu[num]->id][i]);
								i++;
							}
							SePositionner(24, 37);
							for (i=i+1; i<580; i++) printf("%c", descn[p->inventaire->Bolero->contenu[num]->id][i]);
							while (descn[p->inventaire->Bolero->contenu[num]->id][i] != 32 && i<600){
								printf("%c", descn[p->inventaire->Bolero->contenu[num]->id][i]);
								i++;
							}
						}
					}
					else{ // note choisie
						switch(menu->opNotePart){
							case -1 : // choix de l'opération
								SePositionner(60, 7);
								if (num == 1){
									ChangerCouleurTexte(COULEUR_BLEU);
									printf("Déplacer                                                        ");
									ChangerCouleurTexte(COULEUR_BLANC);
									SePositionner(60, 8);
									printf("Enlever                                ");
									SePositionner(60, 9);
									printf("Monter                           ");
									SePositionner(60, 10);
									printf("Descendre");
									SePositionner(60, 11);
									printf("Jeter");
								}
								else if (num == 2){
									printf("Déplacer                                                        ");
									ChangerCouleurTexte(COULEUR_BLEU);
									SePositionner(60, 8);
									printf("Enlever                                ");
									ChangerCouleurTexte(COULEUR_BLANC);
									SePositionner(60, 9);
									printf("Monter                           ");
									SePositionner(60, 10);
									printf("Descendre");
									SePositionner(60, 11);
									printf("Jeter");
								}
								else if (num == 3){
									printf("Déplacer                                                        ");
									SePositionner(60, 8);
									printf("Enlever                                ");
									ChangerCouleurTexte(COULEUR_BLEU);
									SePositionner(60, 9);
									printf("Monter                           ");
									ChangerCouleurTexte(COULEUR_BLANC);
									SePositionner(60, 10);
									printf("Descendre");
									SePositionner(60, 11);
									printf("Jeter");
								}
								else if (num == 4){
									printf("Déplacer                                                        ");
									SePositionner(60, 8);
									printf("Enlever                                ");
									SePositionner(60, 9);
									printf("Monter                           ");
									ChangerCouleurTexte(COULEUR_BLEU);
									SePositionner(60, 10);
									printf("Descendre");
									ChangerCouleurTexte(COULEUR_BLANC);
									SePositionner(60, 11);
									printf("Jeter");						
								}
								else{
									printf("Déplacer                                                        ");
									SePositionner(60, 8);
									printf("Enlever                                ");
									SePositionner(60, 9);
									printf("Monter                           ");
									SePositionner(60, 10);
									printf("Descendre");
									ChangerCouleurTexte(COULEUR_BLEU);
									SePositionner(60, 11);
									printf("Jeter");
									ChangerCouleurTexte(COULEUR_BLANC);
								}
								break;
								
							case 1 : // déplacer
								switch(menu->choixPartition){
									case -1 : // choix de la partition cible
										if (num == 1){
											SePositionner(80, 7);
											ChangerCouleurTexte(COULEUR_BLEU);
											printf("Vers la Sérénade");
											SePositionner(80, 8);
											ChangerCouleurTexte(COULEUR_BLANC);
											printf("Vers l'Hymne");
										}
										else{
											SePositionner(80, 7);
											printf("Vers la Sérénade");
											ChangerCouleurTexte(COULEUR_BLEU);
											SePositionner(80, 8);
											printf("Vers l'Hymne");
											ChangerCouleurTexte(COULEUR_BLANC);
										}
										break;
										
									case 1 : // vers hymne
										break;
									case 2 : // vers sérénade
										break;
								}
								break;
								
							case 2 : // enlever
								break;
							case 3 : // monter
								break;
							case 4 : // descendre
								break;
							case 5 : // jeter
								switch(menu->confirmation){
									case -1 : // demande de confirmation
										SePositionner(80, 7);
										printf("Voulez-vous vraiment jeter cette note ?");
										if (num == 1){
											SePositionner(81, 8);
											ChangerCouleurTexte(COULEUR_BLEU);
											printf("Non");
											SePositionner(81, 9);
											ChangerCouleurTexte(COULEUR_BLANC);
											printf("Oui");
										}
										else{
											SePositionner(81, 8);
											printf("Non");
											ChangerCouleurTexte(COULEUR_BLEU);
											SePositionner(81, 9);
											printf("Oui");
											ChangerCouleurTexte(COULEUR_BLANC);
										}
										break;
										
									case 1 : // non
										break;
									case 2 : // oui
										break;
								}
								break;
						}
					}
					break;
					
				case 2 : // hymne
					potRestant = p->inventaire->Hymne->potentiel - calculPotentielPart(p->inventaire->Hymne);
					if (menu->notePartChoisie == -1){ // choix de la note
						for (i=0; i<25; i++){
							if (i == num){
								ChangerCouleurTexte(COULEUR_BLEU);
								if (p->inventaire->Hymne->contenu[i] != NULL){
									printf("\n\r %s", p->inventaire->Hymne->contenu[i]->nom);
								}
								else printf("\n\r - - - - ");
								ChangerCouleurTexte(COULEUR_BLANC);
							}
							else{
								if (p->inventaire->Hymne->contenu[i] != NULL){
									printf("\n\r %s", p->inventaire->Hymne->contenu[i]->nom);
								}
								else printf("\n\r - - - - ");
							}
						}
						for (i=25; i<50; i++){
							SePositionner(35, i-23);
							if (i == num){
								ChangerCouleurTexte(COULEUR_BLEU);
								if (p->inventaire->Hymne->contenu[i] != NULL){
									printf(" %s", p->inventaire->Hymne->contenu[i]->nom);
								}
								else printf(" - - - - ");
								ChangerCouleurTexte(COULEUR_BLANC);
							}
							else{
								if (p->inventaire->Hymne->contenu[i] != NULL){
									printf(" %s", p->inventaire->Hymne->contenu[i]->nom);
								}
								else printf(" - - - - ");
							}
						}
						
						SePositionner(0, 29);
						printf(">---------Potentiel restant : %d----------<", potRestant);
						if (p->inventaire->Hymne->contenu[num] != NULL){
							SePositionner(2, 32);
							printf("Niveau : %d\n\r ", p->inventaire->Hymne->contenu[num]->niveau);
							printf("Attaque : %d\n\r ", p->inventaire->Hymne->contenu[num]->attaque);
							printf("Défense : %d\n\r ", p->inventaire->Hymne->contenu[num]->defense);
							printf("Points de vie : %d", p->inventaire->Hymne->contenu[num]->pv);
							SePositionner(24, 32);
							for (i=0; i<80; i++) printf("%c", descn[p->inventaire->Hymne->contenu[num]->id][i]);
							while (descn[p->inventaire->Hymne->contenu[num]->id][i] != 32 && i<100){
								printf("%c", descn[p->inventaire->Hymne->contenu[num]->id][i]);
								i++;
							}
							SePositionner(24, 33);
							for (i=i+1; i<180; i++) printf("%c", descn[p->inventaire->Hymne->contenu[num]->id][i]);
							while (descn[p->inventaire->Hymne->contenu[num]->id][i] != 32 && i<200){
								printf("%c", descn[p->inventaire->Hymne->contenu[num]->id][i]);
								i++;
							}
							SePositionner(24, 34);
							for (i=i+1; i<280; i++) printf("%c", descn[p->inventaire->Hymne->contenu[num]->id][i]);
							while (descn[p->inventaire->Hymne->contenu[num]->id][i] != 32 && i<300){
								printf("%c", descn[p->inventaire->Hymne->contenu[num]->id][i]);
								i++;
							}
							SePositionner(24, 35);
							for (i=i+1; i<380; i++) printf("%c", descn[p->inventaire->Hymne->contenu[num]->id][i]);
							while (descn[p->inventaire->Hymne->contenu[num]->id][i] != 32 && i<400){
								printf("%c", descn[p->inventaire->Hymne->contenu[num]->id][i]);
								i++;
							}
							SePositionner(24, 36);
							for (i=i+1; i<480; i++) printf("%c", descn[p->inventaire->Hymne->contenu[num]->id][i]);
							while (descn[p->inventaire->Hymne->contenu[num]->id][i] != 32 && i<500){
								printf("%c", descn[p->inventaire->Hymne->contenu[num]->id][i]);
								i++;
							}
							SePositionner(24, 37);
							for (i=i+1; i<580; i++) printf("%c", descn[p->inventaire->Hymne->contenu[num]->id][i]);
							while (descn[p->inventaire->Hymne->contenu[num]->id][i] != 32 && i<600){
								printf("%c", descn[p->inventaire->Hymne->contenu[num]->id][i]);
								i++;
							}
						}
					}
					else{ // note choisie
						switch(menu->opNotePart){
							case -1 : // choix de l'opération
								SePositionner(60, 7);
								if (num == 1){
									ChangerCouleurTexte(COULEUR_BLEU);
									printf("Déplacer                                                        ");
									ChangerCouleurTexte(COULEUR_BLANC);
									SePositionner(60, 8);
									printf("Enlever                                ");
									SePositionner(60, 9);
									printf("Monter                           ");
									SePositionner(60, 10);
									printf("Descendre");
									SePositionner(60, 11);
									printf("Jeter");
								}
								else if (num == 2){
									printf("Déplacer                                                        ");
									ChangerCouleurTexte(COULEUR_BLEU);
									SePositionner(60, 8);
									printf("Enlever                                ");
									ChangerCouleurTexte(COULEUR_BLANC);
									SePositionner(60, 9);
									printf("Monter                           ");
									SePositionner(60, 10);
									printf("Descendre");
									SePositionner(60, 11);
									printf("Jeter");
								}
								else if (num == 3){
									printf("Déplacer                                                        ");
									SePositionner(60, 8);
									printf("Enlever                                ");
									ChangerCouleurTexte(COULEUR_BLEU);
									SePositionner(60, 9);
									printf("Monter                           ");
									ChangerCouleurTexte(COULEUR_BLANC);
									SePositionner(60, 10);
									printf("Descendre");
									SePositionner(60, 11);
									printf("Jeter");
								}
								else if (num == 4){
									printf("Déplacer                                                        ");
									SePositionner(60, 8);
									printf("Enlever                                ");
									SePositionner(60, 9);
									printf("Monter                           ");
									ChangerCouleurTexte(COULEUR_BLEU);
									SePositionner(60, 10);
									printf("Descendre");
									ChangerCouleurTexte(COULEUR_BLANC);
									SePositionner(60, 11);
									printf("Jeter");						
								}
								else{
									printf("Déplacer                                                        ");
									SePositionner(60, 8);
									printf("Enlever                                ");
									SePositionner(60, 9);
									printf("Monter                           ");
									SePositionner(60, 10);
									printf("Descendre");
									ChangerCouleurTexte(COULEUR_BLEU);
									SePositionner(60, 11);
									printf("Jeter");
									ChangerCouleurTexte(COULEUR_BLANC);
								}
								break;
								
							case 1 : // déplacer
								switch(menu->choixPartition){
									case -1 : // choix de la partition cible
										if (num == 1){
											SePositionner(80, 7);
											ChangerCouleurTexte(COULEUR_BLEU);
											printf("Vers le Boléro");
											SePositionner(80, 8);
											ChangerCouleurTexte(COULEUR_BLANC);
											printf("Vers la Sérénade");
										}
										else{
											SePositionner(80, 7);
											printf("Vers le Boléro");
											ChangerCouleurTexte(COULEUR_BLEU);
											SePositionner(80, 8);
											printf("Vers la Sérénade");
											ChangerCouleurTexte(COULEUR_BLANC);
										}
										break;
										
									case 1 : // vers boléro
										break;
									case 2 : // vers sérénade
										break;
								}
								break;
							case 2 : // enlever
								break;
							case 3 : // monter
								break;
							case 4 : // descendre
								break;
							case 5 : // jeter
								switch(menu->confirmation){
									case -1 : // demande de confirmation
										SePositionner(80, 7);
										printf("Voulez-vous vraiment jeter cette note ?");
										if (num == 1){
											SePositionner(81, 8);
											ChangerCouleurTexte(COULEUR_BLEU);
											printf("Non");
											SePositionner(81, 9);
											ChangerCouleurTexte(COULEUR_BLANC);
											printf("Oui");
										}
										else{
											SePositionner(81, 8);
											printf("Non");
											ChangerCouleurTexte(COULEUR_BLEU);
											SePositionner(81, 9);
											printf("Oui");
											ChangerCouleurTexte(COULEUR_BLANC);
										}
										break;
										
									case 1 : // non
										break;
									case 2 : // oui
										break;
								}
								break;
						}
					}
					break;
					
				case 3 : // sérénade
					potRestant = p->inventaire->Serenade->potentiel - calculPotentielPart(p->inventaire->Serenade);
					if (menu->notePartChoisie == -1){ // choix de la note
						for (i=0; i<25; i++){
							if (i == num){
								ChangerCouleurTexte(COULEUR_BLEU);
								if (p->inventaire->Serenade->contenu[i] != NULL){
									printf("\n\r %s", p->inventaire->Serenade->contenu[i]->nom);
								}
								else printf("\n\r - - - - ");
								ChangerCouleurTexte(COULEUR_BLANC);
							}
							else{
								if (p->inventaire->Serenade->contenu[i] != NULL){
									printf("\n\r %s", p->inventaire->Serenade->contenu[i]->nom);
								}
								else printf("\n\r - - - - ");
							}
						}
						for (i=25; i<50; i++){
							SePositionner(35, i-23);
							if (i == num){
								ChangerCouleurTexte(COULEUR_BLEU);
								if (p->inventaire->Serenade->contenu[i] != NULL){
									printf(" %s", p->inventaire->Serenade->contenu[i]->nom);
								}
								else printf(" - - - - ");
								ChangerCouleurTexte(COULEUR_BLANC);
							}
							else{
								if (p->inventaire->Serenade->contenu[i] != NULL){
									printf(" %s", p->inventaire->Serenade->contenu[i]->nom);
								}
								else printf(" - - - - ");
							}
						}
						
						SePositionner(0, 29);
						printf(">---------Potentiel restant : %d----------<", potRestant);
						if (p->inventaire->Serenade->contenu[num] != NULL){
							SePositionner(2, 32);
							printf("Niveau : %d\n\r ", p->inventaire->Serenade->contenu[num]->niveau);
							printf("Attaque : %d\n\r ", p->inventaire->Serenade->contenu[num]->attaque);
							printf("Défense : %d\n\r ", p->inventaire->Serenade->contenu[num]->defense);
							printf("Points de vie : %d", p->inventaire->Serenade->contenu[num]->pv);
							SePositionner(24, 32);
							for (i=0; i<80; i++) printf("%c", descn[p->inventaire->Serenade->contenu[num]->id][i]);
							while (descn[p->inventaire->Serenade->contenu[num]->id][i] != 32 && i<100){
								printf("%c", descn[p->inventaire->Serenade->contenu[num]->id][i]);
								i++;
							}
							SePositionner(24, 33);
							for (i=i+1; i<180; i++) printf("%c", descn[p->inventaire->Serenade->contenu[num]->id][i]);
							while (descn[p->inventaire->Serenade->contenu[num]->id][i] != 32 && i<200){
								printf("%c", descn[p->inventaire->Serenade->contenu[num]->id][i]);
								i++;
							}
							SePositionner(24, 34);
							for (i=i+1; i<280; i++) printf("%c", descn[p->inventaire->Serenade->contenu[num]->id][i]);
							while (descn[p->inventaire->Serenade->contenu[num]->id][i] != 32 && i<300){
								printf("%c", descn[p->inventaire->Serenade->contenu[num]->id][i]);
								i++;
							}
							SePositionner(24, 35);
							for (i=i+1; i<380; i++) printf("%c", descn[p->inventaire->Serenade->contenu[num]->id][i]);
							while (descn[p->inventaire->Serenade->contenu[num]->id][i] != 32 && i<400){
								printf("%c", descn[p->inventaire->Serenade->contenu[num]->id][i]);
								i++;
							}
							SePositionner(24, 36);
							for (i=i+1; i<480; i++) printf("%c", descn[p->inventaire->Serenade->contenu[num]->id][i]);
							while (descn[p->inventaire->Serenade->contenu[num]->id][i] != 32 && i<500){
								printf("%c", descn[p->inventaire->Serenade->contenu[num]->id][i]);
								i++;
							}
							SePositionner(24, 37);
							for (i=i+1; i<580; i++) printf("%c", descn[p->inventaire->Serenade->contenu[num]->id][i]);
							while (descn[p->inventaire->Serenade->contenu[num]->id][i] != 32 && i<600){
								printf("%c", descn[p->inventaire->Serenade->contenu[num]->id][i]);
								i++;
							}
						}
					}
					else{ // note choisie
						switch(menu->opNotePart){
							case -1 : // choix de l'opération
								SePositionner(60, 7);
								if (num == 1){
									ChangerCouleurTexte(COULEUR_BLEU);
									printf("Déplacer                                                        ");
									ChangerCouleurTexte(COULEUR_BLANC);
									SePositionner(60, 8);
									printf("Enlever                                ");
									SePositionner(60, 9);
									printf("Monter                           ");
									SePositionner(60, 10);
									printf("Descendre");
									SePositionner(60, 11);
									printf("Jeter");
								}
								else if (num == 2){
									printf("Déplacer                                                        ");
									ChangerCouleurTexte(COULEUR_BLEU);
									SePositionner(60, 8);
									printf("Enlever                                ");
									ChangerCouleurTexte(COULEUR_BLANC);
									SePositionner(60, 9);
									printf("Monter                           ");
									SePositionner(60, 10);
									printf("Descendre");
									SePositionner(60, 11);
									printf("Jeter");
								}
								else if (num == 3){
									printf("Déplacer                                                        ");
									SePositionner(60, 8);
									printf("Enlever                                ");
									ChangerCouleurTexte(COULEUR_BLEU);
									SePositionner(60, 9);
									printf("Monter                           ");
									ChangerCouleurTexte(COULEUR_BLANC);
									SePositionner(60, 10);
									printf("Descendre");
									SePositionner(60, 11);
									printf("Jeter");
								}
								else if (num == 4){
									printf("Déplacer                                                        ");
									SePositionner(60, 8);
									printf("Enlever                                ");
									SePositionner(60, 9);
									printf("Monter                           ");
									ChangerCouleurTexte(COULEUR_BLEU);
									SePositionner(60, 10);
									printf("Descendre");
									ChangerCouleurTexte(COULEUR_BLANC);
									SePositionner(60, 11);
									printf("Jeter");						
								}
								else{
									printf("Déplacer                                                        ");
									SePositionner(60, 8);
									printf("Enlever                                ");
									SePositionner(60, 9);
									printf("Monter                           ");
									SePositionner(60, 10);
									printf("Descendre");
									ChangerCouleurTexte(COULEUR_BLEU);
									SePositionner(60, 11);
									printf("Jeter");
									ChangerCouleurTexte(COULEUR_BLANC);
								}
								break;
								
							case 1 : // déplacer
								switch(menu->choixPartition){
									case -1 : // choix de la partition cible
										if (num == 1){
											SePositionner(80, 7);
											ChangerCouleurTexte(COULEUR_BLEU);
											printf("Vers l'Hymne");
											SePositionner(80, 8);
											ChangerCouleurTexte(COULEUR_BLANC);
											printf("Vers le Boléro");
										}
										else{
											SePositionner(80, 7);
											printf("Vers l'Hymne");
											ChangerCouleurTexte(COULEUR_BLEU);
											SePositionner(80, 8);
											printf("Vers le Boléro");
											ChangerCouleurTexte(COULEUR_BLANC);
										}
										break;
										
									case 1 : // vers boléro
										break;
									case 2 : // vers hymne
										break;
								}
								break;
								
							case 2 : // enlever
								break;
							case 3 : // monter
								break;
							case 4 : // descendre
								break;
							case 5 : // jeter
								switch(menu->confirmation){
									case -1 : // demande de confirmation
										SePositionner(80, 7);
										printf("Voulez-vous vraiment jeter cette note ?");
										if (num == 1){
											SePositionner(81, 8);
											ChangerCouleurTexte(COULEUR_BLEU);
											printf("Non");
											SePositionner(81, 9);
											ChangerCouleurTexte(COULEUR_BLANC);
											printf("Oui");
										}
										else{
											SePositionner(81, 8);
											printf("Non");
											ChangerCouleurTexte(COULEUR_BLEU);
											SePositionner(81, 9);
											printf("Oui");
											ChangerCouleurTexte(COULEUR_BLANC);
										}
										break;
										
									case 1 : // non
										break;
									case 2 : // oui
										break;
								}
								break;
						}
					}
					break;
					
				case 4 : // notes d'inventaire
					if (menu->noteInvChoisie == -1){ // choix de la note
						nbrnotes = nombreNotesDiff(p->inventaire->contenuNot);
						cinquieme = nbrnotes/5;
						Nieme = niemeNoteNonVide(num, p->inventaire->contenuNot);
						i=0;
						j=0;
						if (nbrnotes>0){
							do{
								if (j>NBR_DE_NOTES-1) break;
								if (p->inventaire->contenuNot[j].quantite[1] > 0){
									if (i == num){
										ChangerCouleurTexte(COULEUR_BLEU);
										printf("\n\r %s x%d", p->inventaire->contenuNot[j].note->nom, p->inventaire->contenuNot[j].quantite[1]);
										ChangerCouleurTexte(COULEUR_BLANC);
									}
									else{
										printf("\n\r %s x%d", p->inventaire->contenuNot[j].note->nom, p->inventaire->contenuNot[j].quantite[1]);
									}
									i++;
								}
								j++;
							}
							while(i<cinquieme);
							
							do{
								if (j>NBR_DE_NOTES-1) break;
								SePositionner(38, i-cinquieme+2);
								if (p->inventaire->contenuNot[j].quantite[1] > 0){
									if (i == num){
										ChangerCouleurTexte(COULEUR_BLEU);
										printf(" %s x%d", p->inventaire->contenuNot[j].note->nom, p->inventaire->contenuNot[j].quantite[1]);
										ChangerCouleurTexte(COULEUR_BLANC);
									}
									else{
										printf(" %s x%d", p->inventaire->contenuNot[j].note->nom, p->inventaire->contenuNot[j].quantite[1]);
									}
									i++;
								}
								j++;
							}
							while(i<(cinquieme*2));
							
							do{
								if (j>NBR_DE_NOTES-1) break;
								SePositionner(76, i-(cinquieme*2)+2);
								if (p->inventaire->contenuNot[j].quantite[1] > 0){
									if (i == num){
										ChangerCouleurTexte(COULEUR_BLEU);
										printf(" %s x%d", p->inventaire->contenuNot[j].note->nom, p->inventaire->contenuNot[j].quantite[1]);
										ChangerCouleurTexte(COULEUR_BLANC);
									}
									else{
										printf(" %s x%d", p->inventaire->contenuNot[j].note->nom, p->inventaire->contenuNot[j].quantite[1]);
									}
									i++;
								}
								j++;
							}
							while(i<(cinquieme*3));
							
							do{
								if (j>NBR_DE_NOTES-1) break;
								SePositionner(112, i-(cinquieme*3)+2);
								if (p->inventaire->contenuNot[j].quantite[1] > 0){
									if (i == num){
										ChangerCouleurTexte(COULEUR_BLEU);
										printf(" %s x%d", p->inventaire->contenuNot[j].note->nom, p->inventaire->contenuNot[j].quantite[1]);
										ChangerCouleurTexte(COULEUR_BLANC);
									}
									else{
										printf(" %s x%d", p->inventaire->contenuNot[j].note->nom, p->inventaire->contenuNot[j].quantite[1]);
									}
									i++;
								}
								j++;
							}
							while(i<(cinquieme*4));
							
							do{
								if (j>NBR_DE_NOTES-1) break;
								SePositionner(144, i-(cinquieme*4)+2);
								if (p->inventaire->contenuNot[j].quantite[1] > 0){
									if (i == num){
										ChangerCouleurTexte(COULEUR_BLEU);
										printf(" %s x%d", p->inventaire->contenuNot[j].note->nom, p->inventaire->contenuNot[j].quantite[1]);
										ChangerCouleurTexte(COULEUR_BLANC);
									}
									else{
										printf(" %s x%d", p->inventaire->contenuNot[j].note->nom, p->inventaire->contenuNot[j].quantite[1]);
									}
									i++;
								}
								j++;
							}
							while(i<nbrnotes);
							
							SePositionner(0, 34);
							printf(">--------------------------------------------------------------------------------------------------------------------------<");
							SePositionner(2, 36);
						
							printf("Niveau : %d\n\r ", p->inventaire->contenuNot[Nieme].note->niveau);
							printf("Attaque : %d\n\r ", p->inventaire->contenuNot[Nieme].note->attaque);
							printf("Défense : %d\n\r ", p->inventaire->contenuNot[Nieme].note->defense);
							printf("Points de vie : %d", p->inventaire->contenuNot[Nieme].note->pv);
							SePositionner(24, 36);
							for (i=0; i<80; i++) printf("%c", descn[p->inventaire->contenuNot[Nieme].note->id][i]);
							while (descn[p->inventaire->contenuNot[Nieme].note->id][i] != 32 && i<100){
								printf("%c", descn[p->inventaire->contenuNot[Nieme].note->id][i]);
								i++;
							}
							SePositionner(24, 37);
							for (i=i+1; i<180; i++) printf("%c", descn[p->inventaire->contenuNot[Nieme].note->id][i]);
							while (descn[p->inventaire->contenuNot[Nieme].note->id][i] != 32 && i<200){
								printf("%c", descn[p->inventaire->contenuNot[Nieme].note->id][i]);
								i++;
							}
							SePositionner(24, 38);
							for (i=i+1; i<280; i++) printf("%c", descn[p->inventaire->contenuNot[Nieme].note->id][i]);
							while (descn[p->inventaire->contenuNot[Nieme].note->id][i] != 32 && i<300){
								printf("%c", descn[p->inventaire->contenuNot[Nieme].note->id][i]);
								i++;
							}
							SePositionner(24, 39);
							for (i=i+1; i<380; i++) printf("%c", descn[p->inventaire->contenuNot[Nieme].note->id][i]);
							while (descn[p->inventaire->contenuNot[Nieme].note->id][i] != 32 && i<400){
								printf("%c", descn[p->inventaire->contenuNot[Nieme].note->id][i]);
								i++;
							}
							SePositionner(24, 40);
							for (i=i+1; i<480; i++) printf("%c", descn[p->inventaire->contenuNot[Nieme].note->id][i]);
							while (descn[p->inventaire->contenuNot[Nieme].note->id][i] != 32 && i<500){
								printf("%c", descn[p->inventaire->contenuNot[Nieme].note->id][i]);
								i++;
							}
							SePositionner(24, 41);
							for (i=i+1; i<580; i++) printf("%c", descn[p->inventaire->contenuNot[Nieme].note->id][i]);
							while (descn[p->inventaire->contenuNot[Nieme].note->id][i] != 32 && i<600){
								printf("%c", descn[p->inventaire->contenuNot[Nieme].note->id][i]);
								i++;
							}
						}
					}
					else{ // note choisie
						switch(menu->opNoteInv){
							case -1 : // choix de l'opération
								SePositionner(135, 36);
								if (num == 1){
									ChangerCouleurTexte(COULEUR_BLEU);
									printf("Placer                                                   ");
									SePositionner(135, 37);
									ChangerCouleurTexte(COULEUR_BLANC);
									printf("Jeter                                                 ");
								}
								else{
									printf("Placer                                                   ");
									SePositionner(135, 37);
									ChangerCouleurTexte(COULEUR_BLEU);
									printf("Jeter                                                 ");
									ChangerCouleurTexte(COULEUR_BLANC);
								}
								SePositionner(135, 38);
								printf("                                             ");
								break;
								
							case 1 : // déplacer
								if (menu->quantite == -1){ // choix de la quantité
									SePositionner(142, 36);
									printf(" %d", num);
								}
								else{ // quantité choisie
									switch(menu->choixPartition){
										case -1 : // choix de la partition cible
											if (num == 1){
												SePositionner(150, 36);
												ChangerCouleurTexte(COULEUR_BLEU);
												printf("Dans le Boléro");
												SePositionner(150, 37);
												ChangerCouleurTexte(COULEUR_BLANC);
												printf("Dans l'Hymne");
												SePositionner(150, 38);
												printf("Dans la Sérénade");
											}
											else if (num == 2){
												SePositionner(150, 36);
												printf("Dans le Boléro");
												ChangerCouleurTexte(COULEUR_BLEU);
												SePositionner(150, 37);
												printf("Dans l'Hymne");
												ChangerCouleurTexte(COULEUR_BLANC);
												SePositionner(150, 38);
												printf("Dans la Sérénade");
											}
											else{
												SePositionner(150, 36);
												printf("Dans le Boléro");
												SePositionner(150, 37);
												printf("Dans l'Hymne");
												ChangerCouleurTexte(COULEUR_BLEU);
												SePositionner(150, 38);
												printf("Dans la Sérénade");
												ChangerCouleurTexte(COULEUR_BLANC);
											}
											break;
										
										case 1 : // vers boléro
											break;
										case 2 : // vers sérénade
											break;
										case 3 : // vers sérénade
											break;
									}
								}
								break;
								
							case 2 : // jeter
								if (menu->quantite == -1){ // choix de la quantité
									SePositionner(142, 37);
									printf(" %d", num);
								}
								else{ // quantité choisie
									switch(menu->confirmation){
										case -1 : // demande de confirmation
											SePositionner(150, 36);
											printf("Etes-vous certain(e) ?");
											if (num == 1){
												SePositionner(150, 37);
												ChangerCouleurTexte(COULEUR_BLEU);
												printf("Non");
												SePositionner(150, 38);
												ChangerCouleurTexte(COULEUR_BLANC);
												printf("Oui");
											}
											else{
												SePositionner(150, 37);
												printf("Non");
												ChangerCouleurTexte(COULEUR_BLEU);
												SePositionner(150, 38);
												printf("Oui");
												ChangerCouleurTexte(COULEUR_BLANC);
											}
											break;
											
										case 1 : // non
											break;
										case 2 : // oui
											break;
									}
								}
								break;
						}
					}
					break;
			}
			break;
			
		case 2 : // objets
			if (menu->objetChoisi == -1){ // choix de l'objet
				nbrobjets = nombreDobjets(p->inventaire->contenuObj);
				Nieme = niemeObjetNonVide(num, p->inventaire->contenuObj);
				i=0;
				j=0;
				if (nbrobjets>0){
					do{
						if (j>NBR_D_OBJETS-1) break;
						if (p->inventaire->contenuObj[j].quantite > 0){
							if (i == num){
								ChangerCouleurTexte(COULEUR_BLEU);
								printf("\n\r\t%s x%d", p->inventaire->contenuObj[j].objet->nom, p->inventaire->contenuObj[j].quantite);
								ChangerCouleurTexte(COULEUR_BLANC);
							}
							else{
								printf("\n\r\t%s x%d", p->inventaire->contenuObj[j].objet->nom, p->inventaire->contenuObj[j].quantite);
							}
							i++;
						}
						j++;
					}
					while(i<nbrobjets);
					
					printf("\n\n\n\r\t");
					for (i=0; i<80; i++) printf("%c", desco[Nieme][i]);
					while (desco[Nieme][i] != 32 && i<100){
						if (desco[Nieme][i] == '\0'){
							i=-1;
							break;
						}
						printf("%c", desco[Nieme][i]);
						i++;
					}
					if (i!=-1){
						printf("\n\r\t");
						for (i=i+1; i<180 && desco[Nieme][i] != '\0'; i++) printf("%c", desco[Nieme][i]);
						while (desco[Nieme][i] != 32 && i<200){
							if (desco[Nieme][i] == '\0'){
								i=-1;
								break;
							}
							printf("%c", desco[Nieme][i]);
							i++;
						}
					}
					if (i!=-1){
						printf("\n\r\t");
						for (i=i+1; i<280 && desco[Nieme][i] != '\0'; i++) printf("%c", desco[Nieme][i]);
						while (desco[Nieme][i] != 32 && i<300){
							if (desco[Nieme][i] == '\0'){
								i=-1;
								break;
							}
							printf("%c", desco[Nieme][i]);
							i++;
						}
					}
					if (i!=-1){
						printf("\n\r\t");
						for (i=i+1; i<380 && desco[Nieme][i] != '\0'; i++) printf("%c", desco[Nieme][i]);
						while (desco[Nieme][i] != 32 && i<400 && desco[Nieme][i] != '\0'){
							printf("%c", desco[Nieme][i]);
							i++;
						}
					}
					SePositionner(15, 15);
					printf("Redonne %d points de vie.", p->inventaire->contenuObj[Nieme].objet->attribut1);
				}
			}
			else{ // objet choisi
				switch(menu->opObjet){
					case -1 : // choix de l'opération
						SePositionner(15, 22);
						if (num == 1){
							ChangerCouleurTexte(COULEUR_BLEU);
							printf("Utiliser                                                        ");
							ChangerCouleurTexte(COULEUR_BLANC);
							SePositionner(15, 23);
							printf("Jeter                                                      ");
						}
						else{
							printf("Utiliser                                                        ");
							ChangerCouleurTexte(COULEUR_BLEU);
							SePositionner(15, 23);
							printf("Jeter                                                      ");
							ChangerCouleurTexte(COULEUR_BLANC);
						}
						printf("                                                                       ");
						break;
						
					case 1 : // utiliser
						break;
						
					case 2 : // jeter
						if (menu->quantite == -1){ // choix de la quantité
							SePositionner(23, 23);
							printf(" %d", num);
						}
						else{ // quantité choisie
							switch(menu->confirmation){
								case -1 : // demande de confirmation
									SePositionner(35, 22);
									printf("Voulez-vous vraiment jeter cet objet ?");
									if (num == 1){
										SePositionner(36, 23);
										ChangerCouleurTexte(COULEUR_BLEU);
										printf("Non");
										SePositionner(36, 24);
										ChangerCouleurTexte(COULEUR_BLANC);
										printf("Oui");
									}
									else{
										SePositionner(36, 23);
										printf("Non");
										ChangerCouleurTexte(COULEUR_BLEU);
										SePositionner(36, 24);
										printf("Oui");
										ChangerCouleurTexte(COULEUR_BLANC);
									}
									break;
									
								case 1 : // non
									break;
								case 2 : // oui
									break;
							}
						}
						break;
				}
			}
			break;
	}
}
