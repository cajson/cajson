// source file: prog/python.cj
import '../sys/cj.js'
/* 1  */	import * as p from 'https://deno.land/x/python/mod.ts';
/* 3  */	let python=p.python;
/* 4  */	let np=python['import']('numpy');
/* 6  */	let xpoints=np.array([1,8]);
/* 7  */	let ypoints=np.array([3,10]);
/* 9  */	print('xpoints=',xpoints);
/* 10 */	print('ypoints=',ypoints);
/* 12 */	let plt=python['import']('matplotlib.pyplot');
/* 13 */	plt.plot(xpoints,ypoints);
/* 14 */	plt.show();
