#ifndef __MOD_H
#define __MOD_H

#include "base.h"
#include <termios.h>
#include <unistd.h>

typedef struct str_naviguation_menu{
	int noteOuObjet;		/**< Le numéro du menu (1:éditeur - 2:objets */
	int sous_menu_editeur;	/**< Le numéro du sous-menu de l'éditeur (1:Boléro -
							* 2:Hymne - 3:Sérénade - 4:Notes libres) */

	int notePartChoisie;	/**< Numéro de note sélectionnée dans une partition (de 0 à 50) */
	int noteInvChoisie;		/**< Numéro de note sélectionnée dans l'inventaire (de 0 à 150) */
	int objetChoisi;		/**< Numéro de l'objet sélectionné dans l'inventaire (de 0 à 7) */

	int opNotePart;			/**< L'opération à effectuer sur la note de partition sélectionnée */
	int opNoteInv;			/**< L'opération à effectuer sur la note d'inventaire sélectionnée */
	int opObjet;			/**< L'opération à effectuer sur l'objet sélectionné */

	int quantite;			/** La quantité sur laquelle opérer */
	int choixPartition;		/**< La partition dans laquelle déplacer la note. RUN */
	int confirmation;		/**< Demande de confirmation à l'utilisateur (pour jeter). RUN */
}Menu;

/**
 *	\enum	CouleurConsole
 *	\brief	Les couleurs possibles pour écrire dans la console.
 *	Chaque entier correspond à une couleur.
 */
enum CouleurConsole{
	/** Noir. */
	COULEUR_NOIR = 30,
	/** Rouge. */
	COULEUR_ROUGE = 31,
	/** Vert. */
	COULEUR_VERT = 32,
	/** Jaune. */
	COULEUR_JAUNE = 33,
	/** Bleu. */
	COULEUR_BLEU = 34,
	/** Magenta. */
	COULEUR_MAGENTA = 35,
	/** Cyan. */
	COULEUR_CYAN = 36,
	/** Blanc. */
	COULEUR_BLANC = 37
};

/**
 *	\enum	ToucheClavier
 *	\brief	Toutes les touches ou caractères qu'il est possible de récupérer.
 *	Chaque entier correspond à une touche.
 */
enum ToucheClavier{
	/** Touche tabulation horizontale. */
	TOUCHE_TABULATION_HORIZONTALE,
	/** Touche Entrée. */
	TOUCHE_ENTREE,
	/** Touche Échap. */
	TOUCHE_ECHAP,
	/** Touche Espace. */
	TOUCHE_ESPACE,
	/** Touche Retour arrière. */
	TOUCHE_RETOUR_ARRIERE,
	/** Touche Insertion. */
	TOUCHE_INSERTION,
	/** Touche Fin. */
	TOUCHE_FIN,
	/** Touche Page précédente. */
	TOUCHE_PAGE_PRECEDENTE,
	/** Touche Page suivante. */
	TOUCHE_PAGE_SUIVANTE,
	/** Touche Origine. */
	TOUCHE_ORIGINE,
	/** Touche 5 du pavé numérique (ne sert à rien??) */
	TOUCHE_CINQ_PAVE_NUMERIQUE,
	/** Touche Ġ */
	TOUCHE_PUISSANCE_DEUX,
	/** Touche !. */
	TOUCHE_EXCLAMATION,
	/** Touche ?. */
	TOUCHE_INTERROGATION,
	/** Touche ". */
	TOUCHE_GUILLEMETS,
	/** Touche #. */
	TOUCHE_DIESE,
	/** Touche $. */
	TOUCHE_DOLLAR,
	/** Touche %. */
	TOUCHE_POURCENTAGE,
	/** Touche &. */
	TOUCHE_ESPERLUETTE,
	/** Touche (. */
	TOUCHE_PARENTHESE_GAUCHE,
	/** Touche ). */
	TOUCHE_PARENTHESE_DROITE,
	/** Touche *. */
	TOUCHE_ASTERISQUE,
	/** Touche +. */
	TOUCHE_PLUS,
	/** Touche ,. */
	TOUCHE_VIRGULE,
	/** Touche -. */
	TOUCHE_MOINS,
	/** Touche .. */
	TOUCHE_POINT,
	/** Touche /. */
	TOUCHE_SLASH,
	/** Touche \. */
	TOUCHE_ANTISLASH,
	/** Touche :. */
	TOUCHE_DOUBLE_POINTS,
	/** Touche ;. */
	TOUCHE_POINT_VIRGULE,
	/** Touche <. */
	TOUCHE_CHEVRON_GAUCHE,
	/** Touche >. */
	TOUCHE_CHEVRON_DROIT,
	/** Touche =. */
	TOUCHE_EGAL,
	/** Touche @. */
	TOUCHE_AROBASE,
	/** Touche [. */
	TOUCHE_CROCHET_GAUCHE,
	/** Touche ]. */
	TOUCHE_CROCHET_DROIT,
	/** Touche '. */
	TOUCHE_APOSTROPHE,
	/** Touche `. */
	TOUCHE_ACCENT_GRAVE,
	/** Touche ^. */
	TOUCHE_ACCENT_CIRCONFLEXE,
	/** Touche Ḟ. */
	TOUCHE_ACCENT_ROND,
	/** Touche Ẁ. */
	TOUCHE_ACCENT_TREMA,
	/** Touche _. */
	TOUCHE_UNDERSCORE,
	/** Touche |. */
	TOUCHE_BARRE_VERTICALE,
	/** Touche ~. */
	TOUCHE_TILDE,
	/** Touche {. */
	TOUCHE_ACCOLADE_GAUCHE,
	/** Touche }. */
	TOUCHE_ACCOLADE_DROITE,
	/** Touche 0. */
	TOUCHE_ZERO,
	/** Touche 1. */
	TOUCHE_UN,
	/** Touche 2. */
	TOUCHE_DEUX,
	/** Touche 3. */
	TOUCHE_TROIS,
	/** Touche 4. */
	TOUCHE_QUATRE,
	/** Touche 5. */
	TOUCHE_CINQ,
	/** Touche 6. */
	TOUCHE_SIX,
	/** Touche 7. */
	TOUCHE_SEPT,
	/** Touche 8. */
	TOUCHE_HUIT,
	/** Touche 9. */
	TOUCHE_NEUF,
	/** Touche a. */
	TOUCHE_A_MIN,
	/** Touche b. */
	TOUCHE_B_MIN,
	/** Touche c. */
	TOUCHE_C_MIN,
	/** Touche d. */
	TOUCHE_D_MIN,
	/** Touche e. */
	TOUCHE_E_MIN,
	/** Touche f. */
	TOUCHE_F_MIN,
	/** Touche g. */
	TOUCHE_G_MIN,
	/** Touche h. */
	TOUCHE_H_MIN,
	/** Touche i. */
	TOUCHE_I_MIN,
	/** Touche j. */
	TOUCHE_J_MIN,
	/** Touche k. */
	TOUCHE_K_MIN,
	/** Touche l. */
	TOUCHE_L_MIN,
	/** Touche m. */
	TOUCHE_M_MIN,
	/** Touche n. */
	TOUCHE_N_MIN,
	/** Touche o. */
	TOUCHE_O_MIN,
	/** Touche p. */
	TOUCHE_P_MIN,
	/** Touche q. */
	TOUCHE_Q_MIN,
	/** Touche r. */
	TOUCHE_R_MIN,
	/** Touche s. */
	TOUCHE_S_MIN,
	/** Touche t. */
	TOUCHE_T_MIN,
	/** Touche u. */
	TOUCHE_U_MIN,
	/** Touche v. */
	TOUCHE_V_MIN,
	/** Touche w. */
	TOUCHE_W_MIN,
	/** Touche x. */
	TOUCHE_X_MIN,
	/** Touche y. */
	TOUCHE_Y_MIN,
	/** Touche z. */
	TOUCHE_Z_MIN,
	/** Touche A. */
	TOUCHE_A_MAJ,
	/** Touche B. */
	TOUCHE_B_MAJ,
	/** Touche C. */
	TOUCHE_C_MAJ,
	/** Touche D. */
	TOUCHE_D_MAJ,
	/** Touche E. */
	TOUCHE_E_MAJ,
	/** Touche F. */
	TOUCHE_F_MAJ,
	/** Touche G. */
	TOUCHE_G_MAJ,
	/** Touche H. */
	TOUCHE_H_MAJ,
	/** Touche I. */
	TOUCHE_I_MAJ,
	/** Touche J. */
	TOUCHE_J_MAJ,
	/** Touche K. */
	TOUCHE_K_MAJ,
	/** Touche L. */
	TOUCHE_L_MAJ,
	/** Touche M. */
	TOUCHE_M_MAJ,
	/** Touche N. */
	TOUCHE_N_MAJ,
	/** Touche O. */
	TOUCHE_O_MAJ,
	/** Touche P. */
	TOUCHE_P_MAJ,
	/** Touche Q. */
	TOUCHE_Q_MAJ,
	/** Touche R. */
	TOUCHE_R_MAJ,
	/** Touche S. */
	TOUCHE_S_MAJ,
	/** Touche T. */
	TOUCHE_T_MAJ,
	/** Touche U. */
	TOUCHE_U_MAJ,
	/** Touche V. */
	TOUCHE_V_MAJ,
	/** Touche W. */
	TOUCHE_W_MAJ,
	/** Touche X. */
	TOUCHE_X_MAJ,
	/** Touche Y. */
	TOUCHE_Y_MAJ,
	/** Touche Z. */
	TOUCHE_Z_MAJ,
	/** Touche à */
	TOUCHE_A_MIN_GRAVE,
	/** Touche á */
	TOUCHE_A_MIN_AIGU,
	/** Touche â */
	TOUCHE_A_MIN_CIRCONFLEXE,
	/** Touche ã */
	TOUCHE_A_MIN_TILDE,
	/** Touche ä */
	TOUCHE_A_MIN_TREMA,
	/** Touche å */
	TOUCHE_A_MIN_ROND,
	/** Touche æ */
	TOUCHE_AE_MIN,
	/** Touche ç */
	TOUCHE_C_CEDILLE,
	/** Touche è */
	TOUCHE_E_MIN_GRAVE,
	/** Touche é */
	TOUCHE_E_MIN_AIGU,
	/** Touche ê */
	TOUCHE_E_MIN_CIRCONFLEXE,
	/** Touche ë */
	TOUCHE_E_MIN_TREMA,
	/** Touche ì */
	TOUCHE_I_MIN_GRAVE,
	/** Touche í */
	TOUCHE_I_MIN_AIGU,
	/** Touche î */
	TOUCHE_I_MIN_CIRCONFLEXE,
	/** Touche ï */
	TOUCHE_I_MIN_TREMA,
	/** Touche ŵ */
	TOUCHE_ED_MIN,
	/** Touche ñ */
	TOUCHE_N_MIN_TILDE,
	/** Touche ò */
	TOUCHE_O_MIN_GRAVE,
	/** Touche ó */
	TOUCHE_O_MIN_AIGU,
	/** Touche ô */
	TOUCHE_O_MIN_CIRCONFLEXE,
	/** Touche õ */
	TOUCHE_O_MIN_TILDE,
	/** Touche ö */
	TOUCHE_O_MIN_TREMA,
	/** Touche ṫ */
	TOUCHE_DIVISION,
	/** Touche ø */
	TOUCHE_O_BARRE,
	/** Touche ù */
	TOUCHE_U_MIN_GRAVE,
	/** Touche ú */
	TOUCHE_U_MIN_AIGU,
	/** Touche û */
	TOUCHE_U_MIN_CIRCONFLEXE,
	/** Touche ü */
	TOUCHE_U_MIN_TREMA,
	/** Touche ý */
	TOUCHE_Y_MIN_AIGU,
	/** Touche ŷ */
	TOUCHE_THORN_MIN,
	/** Touche ÿ */
	TOUCHE_Y_MIN_TREMA,
	/** Touche F1. */
	TOUCHE_F1,
	/** Touche F2. */
	TOUCHE_F2,
	/** Touche F3. */
	TOUCHE_F3,
	/** Touche F4. */
	TOUCHE_F4,
	/** Touche F5. */
	TOUCHE_F5,
	/** Touche F6. */
	TOUCHE_F6,
	/** Touche F7. */
	TOUCHE_F7,
	/** Touche F8. */
	TOUCHE_F8,
	/** Touche F9. */
	TOUCHE_F9,
	/** Touche F10. */
	TOUCHE_F10,
	/** Touche F11. */
	TOUCHE_F11,
	/** Touche F12. */
	TOUCHE_F12,
	/** Touche Flèche Haut */
	TOUCHE_FLECHE_HAUT,
	/** Touche Flèche Bas */
	TOUCHE_FLECHE_BAS,
	/** Touche Flèche Droite */
	TOUCHE_FLECHE_DROITE,
	/** Touche Flèche Gauche */
	TOUCHE_FLECHE_GAUCHE,
	/** Touche euro. */
	TOUCHE_EURO,
	/** Touche livre. */
	TOUCHE_LIVRE,
	/** Touche Ċ */
	TOUCHE_DEVISE_GENERIQUE,
	/** Touche §. */
	TOUCHE_SECTION,
	/** Touche kanji japonais poisson (sakana) (U9B5A). */
	TOUCHE_KANJI_JAPONAIS_SAKANA,
	/** Touche kanji japonais alcool (sake) (U9152). */
	TOUCHE_KANJI_JAPONAIS_SAKE,
	/** Touche inconnue. */
	TOUCHE_INCONNUE
};

/** Active ou désactive le mode Raw. */
void ModeRaw(int activer);
/** Active le mode Raw. */
void ActiverModeRaw();
/** Désactive le mode Raw. */
void DesactiverModeRaw();

/** Récupère le prochain appui de touche. */
int RecupererAppuiTouche();

/** Efface la console. */
void EffacerEcran();

/** Changer la couleur courante du texte. */
void ChangerCouleurTexte(int couleur);
/** Changer la couleur courante du fond. */
void ChangerCouleurFond(int couleur);

/** Réinitialiser les couleurs. */
void ReinitialiserCouleur();

/** Se positionner dans la console. */
void SePositionner(unsigned int x, unsigned int y);

#endif // __MOD_H
