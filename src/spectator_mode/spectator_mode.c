// spectator_mode.c
#include "miniRT.h"
#include "mlx.h"
#include "mlx_struct.h"
#include <string.h>
#define H 0
#define W 1

void destroy_img(t_pict *img, t_mlx *display) {
    if (img && img->img_ptr) {
        mlx_destroy_image(display->mlx_ptr, img->img_ptr);
        memset(img, 0, sizeof(*img));
    }
}

static bool ensure_lowres_image(t_context *scene) {
    const short scale = scene->spectator_scale > 1 ? scene->spectator_scale : 2;
    const short lw = scene->img[W] / scale > 0 ? scene->img[W] / scale : 1;
    const short lh = scene->img[H] / scale > 0 ? scene->img[H] / scale : 1;

    if (scene->lowres_img.img_ptr && scene->lowres_img.size[W] == lw && scene->lowres_img.size[H] == lh)
        return true;
    destroy_img(&scene->screen_ptr, &scene->lowres_img);
    t_pict n = {0};
    n.imgptr = mlx_new_image(scene->screen_ptr.mlxptr, lw, lh);
    if (!n.imgptr) return false;
    n.addr = mlx_get_data_addr(n.img_ptr, &n.bbp, &n.lsize, &n.endian);
    n.size[W] = lw;
    n.size[H] = lh;
    scene->lowres_img = n;
    return true;
}

static void upscale_nearest(const tpict *src, tpict *dst, short scale) {
    const int lw = src->size[W];
    const int lh = src->size[H];
    const int dw = dst->size[W];
    const int dh = dst->size[H];
    const int s_bpp = src->bbp / 8;
    const int d_bpp = dst->bbp / 8;

    for (int y = 0; y < lh; ++y) {
        const char *srow = src->addr + y * src->lsize;
        for (int x = 0; x < lw; ++x) {
            const unsigned int pix = *(unsigned int *)(srow + x * s_bpp);
            const int X0 = x * scale;
            const int Y0 = y * scale;
            for (int ky = 0; ky < scale && Y0 + ky < dh; ++ky) {
                char *drow = dst->addr + (Y0 + ky) * dst->lsize;
                for (int kx = 0; kx < scale && X0 + kx < dw; ++kx) {
                    *(unsigned int *)(drow + (X0 + kx) * d_bpp) = pix;
                }
            }
        }
    }
}

void render_frame(tcontext *scene) {
    if (!scene->spectator_mode) {
        // Pipeline normal: tracer directement dans l’image plein écran
        // rtscene -> mlx_put_image_to_window (déjà présent dans le projet)
        rtscene(scene);
        mlx_put_image_to_window(scene->screenptr.mlxptr, scene->screenptr.winptr,
                                scene->screenptr.img.imgptr, 0, 0);
        return;
    }

    if (!ensure_lowres_image(scene)) {
        // fallback si allocation lowres impossible
        rtscene(scene);
        mlx_put_image_to_window(scene->screenptr.mlxptr, scene->screenptr.winptr,
                                scene->screenptr.img.imgptr, 0, 0);
        return;
    }

    // Sauvegarde des dimensions et du pointeur image écran
    short saved_img[2] = { scene->img[W], scene->img[H] };
    tpict saved_full = scene->screenptr.img;

    // Bascule temporairement le contexte vers l’image lowres
    scene->img[W] = scene->lowres_img.size[W];
    scene->img[H] = scene->lowres_img.size[H];
    scene->screenptr.img = scene->lowres_img;

    // Met à jour le viewport pour ces dimensions réduites puis trace
    getcamera(scene->camera, scene->img);
    rtscene(scene);

    // Restaure dimensions et image plein écran
    scene->screenptr.img = saved_full;
    scene->img[W] = saved_img[W];
    scene->img[H] = saved_img[H];
    getcamera(scene->camera, scene->img);

    // Upscale lowres -> plein écran
    upscale_nearest(&scene->lowres_img, &scene->screenptr.img, scene->spectator_scale);

    // Affiche
    mlx_put_image_to_window(scene->screenptr.mlxptr, scene->screenptr.winptr,
                            scene->screenptr.img.imgptr, 0, 0);
}

void spectator_destroy(tcontext *scene) {
    destroy_img(&scene->screenptr, &scene->lowres_img);
}

