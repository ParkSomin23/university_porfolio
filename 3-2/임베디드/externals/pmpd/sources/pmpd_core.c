/*
 *  pmpd_core.c
 */

t_float sign_ch(t_float v)
{
    return v > 0 ? 1 : -1;
}

t_float pow_ch(t_float x, t_float y)
{
    return x > 0 ? pow(x,y) : -pow(-x,y);
}

t_float sqr(t_float x)
{
    return x*x ;
}

t_float mix(t_float X, t_float Y, t_float mix)
{
    return (1-mix)*X + mix*Y ;
}

t_float tabread2(t_pmpd *x, t_float pos, t_symbol *array)
{
    t_garray *a;
    int npoints;
    t_word *vec;
    t_float posx;
    
    if (!(a = (t_garray *)pd_findbyclass(array, garray_class)))
        pd_error(x, "%s: no such array", array->s_name);
    else if (!garray_getfloatwords(a, &npoints, &vec))
        pd_error(x, "%s: bad template for tabLink", array->s_name);
    else
    {
        posx = fabs(pos)*npoints;
        int n=posx;
        if (n >= npoints - 1) 
            return (sign_ch(pos)*vec[npoints-1].w_float);
        float fract = posx-n;
        return (sign_ch(pos) * ( fract*vec[n+1].w_float+(1-fract)*vec[n].w_float));
    }
    return( pos); // si il y a un pb sur le tableau, on renvoie l'identité
}

void pmpd_reset(t_pmpd *x)
{
    x->nb_link = 0;
    x->nb_mass = 0;
    x->minX = -1000000;
    x->maxX = 1000000;
    x->grab = 0;
}

void *pmpd_new()
{
    t_pmpd *x = (t_pmpd *)pd_new(pmpd_class);

    pmpd_reset(x);
    
    x->main_outlet=outlet_new(&x->x_obj, 0);
    // x->info_outlet=outlet_new(&x->x_obj, 0); // TODO

    return (void *)x;
}

void pmpd_bang(t_pmpd *x)
{ // this part is doing all the PM
    t_float F, L, absL, tmpX;
    t_int i;
    // post("bang");

    for (i=0; i<x->nb_mass; i++)
    // compute new masses position
        if (x->mass[i].mobile > 0) // only if mobile
        {
			// amplify force that opose to movement
			if (x->mass[i].overdamp != 0)
			{
				tmpX = x->mass[i].speedX * x->mass[i].forceX;
				tmpX = min(0,tmpX); // overdamped only if force opose movment
				tmpX *= -x->mass[i].overdamp;
				tmpX += 1;
				x->mass[i].forceX *= tmpX;
			}

            x->mass[i].speedX += x->mass[i].forceX * x->mass[i].invM;
            // x->mass[i].forceX = 0;
            x->mass[i].posX += x->mass[i].speedX ;
            // x->mass[i].posX = min(x->maxX,max(x->minX,x->mass[i].posX));
            if ( (x->mass[i].posX < x->minX) || (x->mass[i].posX > x->maxX) ) 
            {
                tmpX = min(x->maxX,max(x->minX,x->mass[i].posX));
                x->mass[i].speedX -= x->mass[i].posX - tmpX;
                x->mass[i].posX = tmpX;
            }
            x->mass[i].forceX = -x->mass[i].D2 * x->mass[i].speedX;
        }

    for (i=0; i<x->nb_link; i++)
    // compute link forces
    {
		if (x->link[i].active == 1)
        {
            L = x->link[i].mass1->posX - x->link[i].mass2->posX;
            absL = fabs(L);
            if ( (absL >= x->link[i].Lmin) && (absL < x->link[i].Lmax)  && (L !=0))
            {
                if (x->link[i].lType == 2)
                { // K et D viennent d'une table
                    F  = x->link[i].D * tabread2(x, (L - x->link[i].distance) / x->link[i].D_L, x->link[i].arrayD);
                    F += x->link[i].K * tabread2(x, L / x->link[i].K_L, x->link[i].arrayK);
                }
                else
                {            
                    F  = x->link[i].D * (L - x->link[i].distance) ;
                    F += x->link[i].K *  sign_ch(L) * pow_ch( absL - x->link[i].L, x->link[i].Pow);
                }
            
                x->link[i].mass1->forceX -= F;
                x->link[i].mass2->forceX += F;
				x->link[i].forceX = F; // save for latter use

            }
            x->link[i].distance=L;
        }
    }
}

void pmpd_mass(t_pmpd *x, t_symbol *s, int argc, t_atom *argv)
// t_symbol *Id, t_float mobile, t_float M, t_float posX)
{ // add a mass 
    x->mass[x->nb_mass].Id = gensym("mass");
	if ((argc >= 1) &&  (argv[0].a_type == A_SYMBOL))
		x->mass[x->nb_mass].Id = atom_getsymbolarg(0,argc,argv);
	x->mass[x->nb_mass].mobile = 1;
	if ((argc >= 2) &&  (argv[1].a_type == A_FLOAT))
		x->mass[x->nb_mass].mobile = (int) atom_getfloatarg(1, argc, argv);
	t_float M = 1;
	if ((argc >= 3) &&  (argv[2].a_type == A_FLOAT))
		M = atom_getfloatarg(2, argc, argv);
	if (M<=0) M=1;
	x->mass[x->nb_mass].invM = 1/M;
	x->mass[x->nb_mass].speedX = 0;
	x->mass[x->nb_mass].posX = 0;
	if ((argc >= 4) &&  (argv[3].a_type == A_FLOAT))
		x->mass[x->nb_mass].posX = atom_getfloatarg(3, argc, argv);
	x->mass[x->nb_mass].forceX = 0;
	x->mass[x->nb_mass].num = x->nb_mass;
	x->mass[x->nb_mass].D2 = 0;
	x->mass[x->nb_mass].overdamp = 0;
	x->nb_mass++ ;
	x->nb_mass = min ( nb_max_mass -1, x->nb_mass );
}

void pmpd_create_link(t_pmpd *x, t_symbol *Id, int mass1, int mass2, t_float K, t_float D, t_float Pow, t_float Lmin, t_float Lmax, t_int type)
{ // create a link based on mass number

    if ((x->nb_mass>0) && (mass1 != mass2) && (mass1 >= 0) && (mass2 >= 0) && (mass1 < x->nb_mass) && (mass2 < x->nb_mass) )
    {
        x->link[x->nb_link].lType = type;
        x->link[x->nb_link].Id = Id;
        x->link[x->nb_link].active = 1;
        x->link[x->nb_link].mass1 = &x->mass[mass1]; 
        x->link[x->nb_link].mass2 = &x->mass[mass2];
        x->link[x->nb_link].K = K;
        x->link[x->nb_link].D = D;
        x->link[x->nb_link].L = x->mass[mass1].posX - x->mass[mass2].posX;
        x->link[x->nb_link].Pow = Pow;
        x->link[x->nb_link].Lmin = Lmin;
        x->link[x->nb_link].Lmax = Lmax;
        x->link[x->nb_link].distance =  x->link[x->nb_link].L;

        x->nb_link++ ;
        x->nb_link = min ( nb_max_link -1, x->nb_link );
    }
}

void pmpd_link(t_pmpd *x, t_symbol *s, int argc, t_atom *argv)
{ // add a link : Id, *mass1, *mass2, K, D, Pow, Lmin, Lmax;

    int i, j;

	t_symbol *Id = gensym("link");
	if ((argc >= 1) &&  (argv[0].a_type == A_SYMBOL))
		Id = atom_getsymbolarg(0,argc,argv);
	t_float K = 0;
   	if ((argc >= 4) &&  (argv[3].a_type == A_FLOAT))
		K = atom_getfloatarg(3, argc, argv);
	t_float D = 0;
   	if ((argc >= 5) &&  (argv[4].a_type == A_FLOAT))
		D = atom_getfloatarg(4, argc, argv);
    t_float Pow = 1; 
    if (argc > 5) Pow = atom_getfloatarg(5, argc, argv);
    t_float Lmin = -1000000;
    if (argc > 6) Lmin = atom_getfloatarg(6, argc, argv);
    t_float Lmax =  1000000;
    if (argc > 7) Lmax = atom_getfloatarg(7, argc, argv);
//    post("%d,%d, %f,%f", mass1, mass2, K, D);

    if ( ( argc > 2 ) && ( argv[1].a_type == A_FLOAT ) && ( argv[2].a_type == A_FLOAT ) )
    {
        pmpd_create_link(x, Id, atom_getfloatarg(1, argc, argv), atom_getfloatarg(2, argc, argv), K, D, Pow, Lmin, Lmax, 0);
    }
    else if ( ( argc > 2 ) && ( argv[1].a_type == A_SYMBOL ) && ( argv[2].a_type == A_FLOAT ) )
    {
        for (i=0; i< x->nb_mass; i++)
        {
            if ( atom_getsymbolarg(1,argc,argv) == x->mass[i].Id)
            {
                pmpd_create_link(x, Id, i, atom_getfloatarg(2, argc, argv), K, D, Pow, Lmin, Lmax, 0);
            }
        }
    }
    else if ( ( argc > 2 ) && ( argv[1].a_type == A_FLOAT ) && ( argv[2].a_type == A_SYMBOL ) )
    {
        for (i=0; i< x->nb_mass; i++)
        {
            if ( atom_getsymbolarg(2,argc,argv) == x->mass[i].Id)
            {
                pmpd_create_link(x, Id, atom_getfloatarg(1, argc, argv), i, K, D, Pow, Lmin, Lmax, 0);
            }
        }
    }
    else if ( ( argc > 2 ) && ( argv[1].a_type == A_SYMBOL ) && ( argv[2].a_type == A_SYMBOL ) )
    {
        for (i=0; i< x->nb_mass; i++)
        {
            for (j=0; j< x->nb_mass; j++)
            {
                if ( (atom_getsymbolarg(1,argc,argv) == x->mass[i].Id)&(atom_getsymbolarg(2,argc,argv) == x->mass[j].Id))
                {
                    if (!( (x->mass[i].Id == x->mass[j].Id) && (i>j) )) 
                    // si lien entre 2 serie de masses identique entres elle, alors on ne creer qu'un lien sur 2, pour evider les redondances
                        pmpd_create_link(x, Id, i, j, K, D, Pow, Lmin, Lmax, 0);
                }
            }   
        }
    }
    else
		pmpd_create_link(x, Id, 0, 1, K, D, Pow, Lmin, Lmax, 0);
}

void pmpd_tabLink(t_pmpd *x, t_symbol *s, int argc, t_atom *argv)
{
    int i, j;
    
    t_symbol *Id = atom_getsymbolarg(0,argc,argv);
    int mass1 = atom_getfloatarg(1, argc, argv);
    int mass2 = atom_getfloatarg(2, argc, argv);
    t_symbol *arrayK = atom_getsymbolarg(3,argc,argv);
    t_float Kl = atom_getfloatarg(4, argc, argv);
    if (Kl <= 0) Kl = 1;
    t_symbol *arrayD = atom_getsymbolarg(5,argc,argv);    
    t_float Dl = atom_getfloatarg(6, argc, argv);
    if (Dl <= 0) Dl = 1;
    
    if ( ( argv[1].a_type == A_FLOAT ) && ( argv[2].a_type == A_FLOAT ) )
    {
        pmpd_create_link(x, Id, mass1, mass2, 1, 1, 1, -1000000, 1000000, 2);
        x->link[x->nb_link-1].arrayK = arrayK;
        x->link[x->nb_link-1].arrayD = arrayD;
        x->link[x->nb_link-1].K_L = Kl;
        x->link[x->nb_link-1].D_L = Dl;    
    }
    else
    if ( ( argv[1].a_type == A_SYMBOL ) && ( argv[2].a_type == A_FLOAT ) )
    {
        for (i=0; i< x->nb_mass; i++)
        {
            if ( atom_getsymbolarg(1,argc,argv) == x->mass[i].Id)
            {
                pmpd_create_link(x, Id, i, mass2, 1, 1, 1, -1000000, 1000000, 2);
                x->link[x->nb_link-1].arrayK = arrayK;
                x->link[x->nb_link-1].arrayD = arrayD;
                x->link[x->nb_link-1].K_L = Kl;
                x->link[x->nb_link-1].D_L = Dl;    
            }
        }
    }
    else
    if ( ( argv[1].a_type == A_FLOAT ) && ( argv[2].a_type == A_SYMBOL ) )
    {
        for (i=0; i< x->nb_mass; i++)
        {
            if ( atom_getsymbolarg(2,argc,argv) == x->mass[i].Id)
            {
                pmpd_create_link(x, Id, mass1, i, 1, 1, 1, -1000000, 1000000, 2);
                x->link[x->nb_link-1].arrayK = arrayK;
                x->link[x->nb_link-1].arrayD = arrayD;
                x->link[x->nb_link-1].K_L = Kl;
                x->link[x->nb_link-1].D_L = Dl;    
            }
        }
    }
    else
    if ( ( argv[1].a_type == A_SYMBOL ) && ( argv[2].a_type == A_SYMBOL ) )
    {
        for (i=0; i< x->nb_mass; i++)
        {
            for (j=0; j< x->nb_mass; j++)
            {
                if ( (atom_getsymbolarg(1,argc,argv) == x->mass[i].Id)&(atom_getsymbolarg(2,argc,argv) == x->mass[j].Id))
                {
                    if (!( (x->mass[i].Id == x->mass[j].Id) && (i>j) )) 
                    // si lien entre 2 serie de masses identique entres elle, alors on ne creer qu'un lien sur 2, pour evider les redondances
                    {
                        pmpd_create_link(x, Id, i, j, 1, 1, 1, -1000000, 1000000, 2);
                        x->link[x->nb_link-1].arrayK = arrayK;
                        x->link[x->nb_link-1].arrayD = arrayD;
                        x->link[x->nb_link-1].K_L = Kl;
                        x->link[x->nb_link-1].D_L = Dl;    
                    }
                }
            }   
        }
    }
}

