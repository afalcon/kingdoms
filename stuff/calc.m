ks := (yt - yb) / (xt - xb)
kl := (y2 - y1) / (x2 - x1)
a := {(ms - ml) / (kl - ks) - xt,
      (ms - ml) / (kl - ks) - xb,
      (ms - ml) / (kl - ks) - x1,
      (ms - ml) / (kl - ks) - x2,
      (kl * ms - ks * ml) / (kl - ks) - yt,
      (kl * ms - ks * ml) / (kl - ks) - yb,
      (kl * ms - ks * ml) / (kl - ks) - y1,
      (kl * ms - ks * ml) / (kl - ks) - y2
     }

ml1 = y1 - kl * x1
ml2 = y2 - kl * x2
ms1 = yb - ks * xb
ms2 = yt - ks * xt

ms = ms1
ml = ml1
r0 = Simplify[a]

ms = ms2
r1 = simplify[a]

ml = ml2
r3 = simplify[a]

ms = ms1
r2 = Simplify[a]
