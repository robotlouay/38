
const LV_KEY='ard-lv';
function getLv(){try{return localStorage.getItem(LV_KEY)||'std'}catch(e){return 'std'}}
function setLv(v){try{localStorage.setItem(LV_KEY,v)}catch(e){}applyLv(v)}
function applyLv(v){document.body.classList.remove('lvl-kid','lvl-std','lvl-pro');document.body.classList.add('lvl-'+v);
 document.querySelectorAll('.age button').forEach(b=>b.classList.toggle('on',b.dataset.v===v));
 document.querySelectorAll('.tabs[data-lvtabs] button').forEach(b=>{if(b.dataset.v===v)b.click()});}
function tab(btn){const g=btn.parentNode;g.querySelectorAll('button').forEach(b=>b.classList.toggle('on',b===btn));
 const box=g.parentNode;box.querySelectorAll(':scope > .pane').forEach(p=>p.classList.toggle('on',p.dataset.v===btn.dataset.v));}
function mk(n){document.querySelectorAll('.pic').forEach(p=>{p.classList.toggle('dim',n>0);p.querySelectorAll('.mk').forEach(m=>m.classList.toggle('on',+m.dataset.n===n))});
 document.querySelectorAll('.legend li').forEach(l=>l.classList.toggle('on',+l.dataset.n===n));}
function copyCode(b){const t=b.parentNode.querySelector('pre').innerText;navigator.clipboard&&navigator.clipboard.writeText(t);b.textContent='✓ تم النسخ';setTimeout(()=>b.textContent='نسخ الكود',1500)}
function answer(b,ok){const q=b.closest('.quiz');if(q.dataset.done)return;q.dataset.done=1;
 q.querySelectorAll('button').forEach(x=>{if(x.dataset.ok==='1')x.classList.add('ok')});if(!ok)b.classList.add('no');
 q.querySelector('.fb').textContent=ok?'🎉 أحسنت! إجابة صحيحة':'❌ ليست هذه — الإجابة الصحيحة باللون الأخضر';}
// resistor calculator
const RC=[['أسود','#111827'],['بني','#92400e'],['أحمر','#dc2626'],['برتقالي','#f97316'],['أصفر','#facc15'],['أخضر','#16a34a'],['أزرق','#2563eb'],['بنفسجي','#7c3aed'],['رمادي','#6b7280'],['أبيض','#f8fafc']];
function fmtOhm(v){if(v>=1e6)return +(v/1e6).toFixed(2)+' MΩ';if(v>=1e3)return +(v/1e3).toFixed(2)+' kΩ';return +v.toFixed(2)+' Ω'}
function rcalc(){const a=+document.getElementById('b1').value,b=+document.getElementById('b2').value,m=+document.getElementById('bm').value;
 const v=(a*10+b)*Math.pow(10,m);document.getElementById('rv').textContent=fmtOhm(v)+'  ±5%';
 [['rb1',a],['rb2',b],['rbm',m]].forEach(([id,i])=>document.getElementById(id).setAttribute('fill',RC[i][1]));}
function ohm(){const V=parseFloat(document.getElementById('ov').value),F=parseFloat(document.getElementById('of').value),I=parseFloat(document.getElementById('oi').value);
 const R=(V-F)/(I/1000);document.getElementById('orr').textContent=R>0?('R ≈ '+Math.round(R)+' Ω  → استعمل '+[100,150,220,330,470,560,680,1000].find(x=>x>=R)+' Ω'):'تحقّق من القيم';}
// explorer
function ex(k){document.querySelectorAll('.hot').forEach(h=>h.classList.toggle('on',h.dataset.k===k));
 document.querySelectorAll('.chipb').forEach(h=>h.classList.toggle('on',h.dataset.k===k));
 const d=EXP[k];if(!d)return;document.getElementById('exn').textContent=d.n;document.getElementById('exk').textContent=d.kid;document.getElementById('ext').textContent=d.t;document.getElementById('exa').href=d.u;}
// search
function filt(q){q=q.trim().toLowerCase();document.querySelectorAll('.tile').forEach(t=>{t.style.display=!q||t.dataset.s.includes(q)?'':'none'});
 document.querySelectorAll('.chap').forEach(c=>{c.style.display=[...c.querySelectorAll('.tile')].some(t=>t.style.display!=='none')?'':'none'})}
// big quiz
function bigQuiz(){const box=document.getElementById('bq');const qs=[...QZ].sort(()=>Math.random()-.5).slice(0,8);let sc=0,dn=0;
 box.innerHTML=qs.map((q,i)=>`<div class="quiz box" data-i="${i}"><div class="q">${i+1}. ${q.q}</div><div class="opts">${q.o.map((o,j)=>`<button data-ok="${j===q.a?1:0}">${o}</button>`).join('')}</div><div class="fb"></div></div>`).join('')+'<div id="bqs" class="box" style="text-align:center;font-size:22px;font-weight:900"></div>';
 box.querySelectorAll('.quiz button').forEach(b=>b.onclick=()=>{const q=b.closest('.quiz');if(q.dataset.done)return;const ok=b.dataset.ok==='1';answer(b,ok);if(ok)sc++;dn++;
  if(dn===qs.length)document.getElementById('bqs').textContent=`نتيجتك: ${sc} / ${qs.length} `+(sc>=6?'🏆 ممتاز!':sc>=4?'👍 جيد، راجع البطاقات':'📚 شاهد الفيديوهات وحاول من جديد')});}
document.addEventListener('DOMContentLoaded',()=>{applyLv(getLv());if(typeof EXP!=='undefined')ex('mcu');if(document.getElementById('b1'))rcalc();if(document.getElementById('ov'))ohm();if(document.getElementById('bq'))bigQuiz();});
