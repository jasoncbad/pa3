/* --------------------------------

  BigIntegerTest.c | PA3
  Programmer: Jay Montoya
  UCSC ID: jaanmont | 1742317

  Test client for BigInteger ADT for pa3.

-----------------------------------
*/
#include <stdio.h>
#include <stdlib.h>
#include "BigInteger.h"

// main
int main(int argc, char* argv[]) {

  // create a big integer list
  BigInteger A, B, C;

  // string to test on
  char myString9[] = "5063479743559270837748541521867326580790813736536536935752195341230937794271875104732666112319128843773802523291485712588538420010720852497182647513457111705838048066859075915431794917020747167767780561505730928477558855022560775490590700349394000601931349843503682130360056528567664331567048740747379102995581818143698626665268874705343806498625777136234371817747019732485985879931631368152061302562176750651418979810878491947292144831147935294943857746622667850358296131439618581433418464070148658440220383932147326329460690209472527008933254362045166370347027905162152057505930259381319867719443746303101029561941711740726255051649312482887871621242581623023732329206320366199594343059601788301121792669160124485248855545139233458480264244140334874108655812884754087559459076521949423575229051238238722366062258526680577273757088358071841492199078319162139824578057614481580970639233972807240305781972994175827677324235359934651898400780488691094804999087062711580968714030012416334696604932801531861828116387454761892725061336497789385923015600770558291923828865041173082993026840413047715103501560488046490472754337614374367247135365930726170356140216072310670331107648007455431504038721233968386829183562022307334301006485970531900109049356683666508290012440870581944131587022243529113262430206500123753148354843746516769714170696078005096311574102156157204100347627567104977795312796039679363780052617464594649529140084107248951756419263122946453487111729340642102416715815707742213843850716525403527643803457973602948885335967313957176837992825463462677000806769305406253990173493430855402007717839401224393765950111989652079473274318470793973499433388675109229701920707211026105530344568859996098441011546279134935252532688639885045574641413609096067199873952124362368538179218118345616322638441409391147563661160077557650906938425461743849382162049564153809395657687730107180398401354757935983888104786218666147613811835760805703172650591614075094994825155325951128119636321996342967374731372823686423665898810013524995210225681988504112020329551329425736595070634351352477221339527349613244060969096652563073593397197672794226845353002520994424817525298815585916745892796759461347956361059120685967365214060099526554367304705150053322024461294699298585385487372521569629845649610696835285972587959997239987861599217750579221725941740473545879242968710095103063628467518251330327302051291983971781647773338183508486816515685185300965278521826105972845189296033480786292507565858273391102002794763504594501023957633174264454269049682325988808533566933401567299858935563350352713707132488508226085042473159314929594806165626434475467369276207608234379506811581367184178212143866750291883848408612196152595458074604158078695057114074737871089914852395754298555714676064655286131254318485434422501847960957748085866835034577305407168157457200834536604645761468168396462622406124612624606507799114499528401889475080558684346191883221254785687763647117670029245220340115313996921328081821322027293906924419142449942621559155287785627674975343363211379313149506069437724526686059963074448272674893447675489790574882929352041164659896320845233732922314964500733344430458720676388429438991279537197178273622828059340342849523914642939054940702472848711498652243227023406281575496410005165760659192867257033485703428075621800950443294962268182196597509532964577945490405484078184905661797759346344151166759478739551948566345000045602198403067829394818363346748301226816911476430686887826308738927556057933199765956248027467842888416106727584982249123862701140453988046916319614551630653312094202922623880499502927981720456496538272381058530551502441870762352379288199293348500151188710108057586607618629382272171934507612544256440142781767617606992695200357919335996265557142166804940273472151550543659029497957194737781156051000623177109321545683492028218867458747911813039463924427669133714983847938602446791703125131352879109106279273072983645087093280806889413248565541557656524512015469085477555754174122741200117328937893416968882205148173180667912451434923805591943398244171409533193359529906945634386108716340871045227324276851330783910394234443872378659684743855245369729743657962049282694230855139498934317317533933905682662259921311625576086361881610772334822346785353199426982931653724647508740713343332605769573189411989595933105023871663500324324308374142770425517089553443979787858212809911917696516450572929615592269118411082145794791138046721720649013931668037673315157949474027651364995862734589024776098221296318718974189947881592240086548862681851339922787389580351043520278697895459297081378368512131470995683152031744309427655029540902381521171033269412229640409429434110149458591950373838388530570560959919601830762008522917284299824818455999870914919371373188285496830600960594170644905721961813832336660787432859927871067771021571979536937565261832488741097386949104960593484977492650305440577161735828908478211885296523011798828147017870188675888027372757835929457561237062673304066183571840333231999438131693244841565403393236620177498452676223893557155905863692032212884055162364545211937455343258129342466025242844825906017488200482495494541899378781525419979430257485231124207605853138545490656043039422864043503804187845543285371903386577825004291261624146418391803617943840667511531525987427653878665282031899347164039079622054431596956609280825683905314794561602228193156021273299426886730696821665664277667364691609705100829905281553859382567804349261496874874504468232668707888387747240694023568624823161437107100653027453711146740489190844253112056012984846550118832170820427863224547839988537744905677084577053299413532575747414180438155449024751680495826372982087969768821244727994055003702303882282018246026234865130241335013028032223864533779402807099905437343925120292484238619602860734431140013774416977585469038619821584683261113973217671033070076456975353441074831837173942820258657547539097533283450896560765485441778283795804844220617159184393613800426461461601671240694390657679833613552154023212796605852339727947784501912059936897591025582867383402476358997168474811381893162556601204072328181273658813577422071933079654775004385339887398088435502695858201117444460748864023343714882725667655248039568807014163511492654942394581621136443999067977370698796663319666799351820874297657747852815125338146785800892691879750868122184188123155774989014421909563112720049765136002631296905081785216490820298075544400813718888738992587067717787739504768902777320313819420273865683766569798603276238197834742841315277652779582892217222639761673171474779145767935888825283116424367827762658039389544927608953883776400900200732089980408124704534556136410389550526215786174583674449929385121931587414841300336001870259716618247510024940651185218284316681372191510025745771449216388458433568468821420017079463514057186418806621891708191534652372911989872425371827036739501402004307288108513120961321941813209071487816747013473160864201080530059111292318450494821240776452865667326437521062122691960770389140533212194831260639271975306064708491121842065274889676911297155958810559061858175946099778638755778163205399063535130013173495456328226760066042870961738438460009099478049910824387433063109609654275416808966806790302674431645554366609960271046649538261597445988617298879292814886275127998241825232602813739159695433460602078323160188644902562574119986825072485180570194803087567666941916695297843072158801560810622129202652232964838693149250204553915412561879827975029132099412744447685531992828521472266067593602991930077674319512019877177658691866130281018018281197850361945897426594200748047653057324287307392047534746559103741214273810135898388051348522845400565644232191304147287897298997457688558130688493822441816883126686714137634763529328450040469111715701706228951500309189096216322881083244371473387988872396276856562345102179434506994903532560324733594816530094082122096114589717056817561609536196135995095067211187503227531566529239972437361256143369553375049776908173110698492285760080070110121780387796534888795647240561876163970597961916789235501326876134118251962732978997081562943234467162303698487047421175803790395737141215535081920190501854492868789746030718365436753766436536600073657583234035326001780137596181736969354802808050404382128345419264565810154886034317847742161882685183839672364600244224310198052162285406412950311709024340429432746216631282804024809478726578089801818896008698017597552788804135270429422173537335376580519218155911838586210763738990667177738768627762865135994312221899621379526987369114712920846388960330957828923813939545457472328316709457506361903091036030992344918263842124421226422367336483905928723534470842397772073437716850243109917758020994577124327313968053819070609963788572771953445375844824418413034474762710094940016927801215001616035164545135850742122699987529545507563863760235212400434658783950625593790898730360298385414411356776820346286878064513708129593542829482906363143008980717743690912940548221609996588975483464710699764505634873406641441219143706575096946419505862395827228347612944922291729106136539114391871945873370553760048644427552698052092817903678604717884800055360159577093997497013416733880814076241973967993537432958638086930369729942897563978803333664967630175483884050724052876387642096597162832451141856068193210179021164402122446841107003564913257437024085563891153546795420845741897595360185071268434344079733165519286416888823424700587162561966502665185773318988886858972024433743323142317799123314241417106398114779985316838608975084106830531187075219988925186852670544571258777993656526775671299795290997510088877746045898528778317498933053146926916595186041207700985969895590999272973995541180795564026242770185238943492694981993865028119684455943178454930073994085732940354932880775953870071483096962195793569843071995411655325221922006992560999767485786151741201365541264138520472494560467906726142111706840515062884277549539850197623061733806361399038037150";
  char myString8[] = "-1744881811012215068403854719214010825906550732750264236481254070998337135131466399193358996035724337585099592172087402456455717776736794427942327613163965429834470422357221697306772540430985265284913631522208962007529251073628726621538962225601055824686893585491945634099053626243696629011425120604499716712955624400623862161085898355857238113439929174102282057233688145260451369546896193866377593096668019391175291473928442594373761776702490123518664001849966613419823790166918575073357986994491625807132288890641865681186611068690312434327015870779519640378577972971580202626805376734848491387471727028784850145333960888626463255416225569962996933877480765986594875112568631548298988835137602589965676107183287618662208309694484333873768728801971413822564140165985551008230357668223460470861986648739750387270279679676920724702677368619592472689634831341453146807019742756372121804901939329936793437101545762726750219476216550864139819075196628000098698748417802146803868630061023025032080431855592737001868020374406818069170976730806702233160332796247592976063648466360603401585390466649551082827049680001574714337172168814842721474705049173796187240937197491294075270603025815051845802160437516616157328051735695783991535831604337019055865980876002141025893665124800861942685142571711092754574264100614934176919468185821213711420367988467099232744595680717107012763251745668511925034007584314304452464382333459852371041463086338016742885317465047665538124005509735833610731442991959357765767576727741649287577375414761373798230578050225729324875750532459255517474341334313547751426455634423373161358194787234390917498349888327151109671420223415749990218289614591179952182568006601430450367929950010556211244792856044681109995234090689699544374561929109439834294475719882129347240909032586398942129471780267916715381062637004471290214011093710037673265093265200845415579033665568757694293173489048972058263614854447532999276965849890173771382325579197958482533197892941069494988804885796021140378321592923974816673223725869030789889167291413653194670065226161531232719050884301951175211760666775591512276878956019677617238394287007809265383578376671151047383769384003072377440623117938626277048078800407552243340919880394542092469955974576407773416739450299516589243505926489844037772893545644827359923120600799459189055686714005926930711274126142166584812135553088701855042366829299856750667032747573367296662209221505178283198011010775424784323176641960851854246813894414997034392829501018681236512627367225888186484344418580712340030463947791462944993469985047496026238120536853189214542672259036654346999671912372360374548575420724338792590338128665880179097710231746345551773664139405967117801939299653465308429274465700684427992159037896775716747100665645460558787603465019997804151554485920916579189092975236832194282291419515452844976210327410619601809940473675493769314889122955418783410331024737315214547078850184573523268772200203908650113163774614226890555591630943522451927720387464847194974694120108426827100101713776105927786197345284303695231516762650718955335446280011958871644555062539378827879367023521107879737173603304502033071379237818175946796428352430878944986959365346328378852237970054914443189089277509039596416732748254121994572753446487524476140305921657583759836178005715589920580580163558732605190740071779807061147774540682273568388776026386392761850130921111096034896601702343256960659875440208141650738969195493936560709535322337345603121847487490144815119220003549165223831423354831776578280425455410981524740512930926267636235580789159877420250068930362317825372978799086519613550535652389672445475410806788516364308701102379950086989798067187343665303010734593767500344805575472535248552438256828414675119761981301297097903181773024345945651890292090828177926935157487909561330711482525782961257088880702972043706932769750251513499864704955492868960926713703872775666834556371846373281853586499759787239184528849612150979077661740439852850903120708324581011675936731857625777039524613390483726956954608468009031607476995255698382061453455227131895694189194789931747481031319067180429348275639312866681645098158924153552394967046760032750728944674903154681016283852838581069236387663379590460773885809855204396673333005120989765622375235846987694475583279121712905429959975052743941459439412775521730512163699459583225255555906919588737690899180855749460759726154865000931252193688301269796743334924513773338734734528754082638463129310167648212674393299558453204424567799936752960914414804352241622244132899430976238748672206823411442872981353503242523263093159021762532666961739967900880989784444711998606685355689335554216251988986268827268812312810534329475794767302669536216648472096572090653288289990996326509440890139935101457520266718998952219932183987103493849367924627434744203458257588858734907589365720806573673155469932701704987336191770604220210218259227713117808340850747928024314347972433112179328724269354254024488387119591735668535844725101370321242384913943243257466108436665571700775817266995079298283873693294145570742268196580288709551520661011950418041489847555697896455395129602795552365002053571076758181826051185154223387551637815545671622043532284864920058512287110671146516841088108796603587334087707035005835602083223989877521197604584843734945368524247827541570641416667680866948880647524562232971215410107310607528868764876818865697489026092352674742108508041891664788244682413351384203802193406905232703446067507082354670898009882184200264962097129592741071882085129431979853396072173353986761068790632317129056823492436727835232195107839382697590646037233205534340582597060522166532059693014273539915999445366548488381987765897387875202501368721845018646835598420835439425213754881282877001871656340568934028464559643157012558922910127171529603335579581549282348722229994720397826847740641368430516825874231541189881030800195285260634174458077747852451738912658057661737458147088555638468093204093715252643558021836382459128015844096932178167681033081952143552572375213156744862010783643908918527140399663004173091215179620629709701433735647226534499130942784969194398677599691954032272671526405780422464655975319940417886073163819699922957693988162597491676923253903434144060284061051742362217660664383301952983099055948892772394333922917220541157111742026852388182768297022182208583246851856458246430787615515397306678590589487967653796153048878508531076922039917083576587009594686108545194914086816657941783380182005852364274980665851173767675475169344010442497790639160628302674327891505922408880673378127481593408710449701068819042059222271971560687670804694198617778309314849740141966091546566831491089280443532090679768746426680955719490752822950977427824588710470168827154315086340078755024582765671213568476388794041273059919917368284784971589260107602510433987438943363295563413378090181458337160527684839481699641566286981426154005150779451637157052067393975776803948217464913445282046017816212865120014014813688422086594552911008708326264263136075063842442798497220298570205537927647791676114193177264242687051717626845780566663618700856157713490767734804677793393573621118740972363653653530429861088760544518940498343164700090181272015126189324356046970306749096689700645142927013901008761839768912466938203362123399703587505099620531541828517827035612707073994688366880686090668208456438555329810638917266447448140387276202424221293499202308293824244476935930070061965863851081369782238205147670351741406571815225284590450322574019421372383299345987697444281920784586688469712544821843091138640588389577506041537131985548808295508774423472670573129678720693408754478414576716459442947548381655239611831620745178689548461266731598091149967467907324513140752720100631588298623599859693455823259460945221460088828590502350299280176542588321154452074460802446797549915083961313559466457260770348036814082433769279472801330789147653910752028431432292677341527041826968537398872289594555090214831727517539845171180342132832686039573869087705006141800362098967168722160300034234595127512886116581033581630952319276624064451122269672677680362097516382822322383481392355336998447738736452962329393135687519190778322949080304153929718137352366888545687453347316313120017267573994504758834328223658446912505821148845419690342878108373544558429159824883234429584178326023780909554318029749925922854597273327641185090409730399168492956288393108262692047994758070549164141405588339658627827866717391301808906022560139098322067045080773127799770115092447152773641195020447804702510566102840822133622697819517664302684373155951992870699131531981546231814704303092346997405360651235917557683418853150418080814365074996241332851040831199080183008352775348079632980020818392304239875147259446109324074105003295277652370645005019748810299793242155019432368954702508612139116531290722502013711574954446014377908963178791526375818225540881011807149670775227750724871651033406591480211472745359892018837758091303088132080476052545604970297599187590310706873631064701417943251952165815277727555194615297411150297818050948155623433536962348971415564051696322932781047028969425060554385475730298900874553117032796926819492944753820145977944974654367290673902129414683111245586844615552748357459571137347049033656093706424922096890886991710161798723147886478882661948341368394438772115014421908865495668786560586342306661833320710013408612313073690759264534839754784392480898029514979975489267281805081942309129424961457580121701238640511150640916819431301197073521727300220545192295455656693212014713159218775147298754510778683274621189194896633589913029923542388317495708463347479503317688581003872784792167720689757362798371321837308260416576923476651299360219442663778394681771221593627726813873816824370071085678037867669463051605745218377648461323661078522767844109346643784756452328580733869368918069594834094613704818576870623458449087229952120264924453956101862158598018615095194190452118621047253219813135713301113783534083097768960";

  // create the big integer
  A = stringToBigInteger(myString9);
  B = stringToBigInteger(myString8);

  printBigInteger(stdout, A);
  printBigInteger(stdout, B);

  //negate(A);    // test negate

  // testing sum
  printf("\nTESTING SUM: A + B\n");
  C = sum(A, B);
  printf("\n");
  printBigInteger(stdout, C);


  printf("\nTESTING DIFF: A = B\n");
  BigInteger D;
  D = diff(A, B);
  printf("\n");
  printBigInteger(stdout, D);

  //printBigInteger(stdout, A);

  // testing add
  /*printf("\nTESTING ADD: C = A + B");

  add(C, A, B);
  printf("\n");
  printBigInteger(stdout, C);*/


  // test makeZero
  printf("\nTESTING makeZero(): \n");
  makeZero(A);  // test makeZero
  printBigInteger(stdout, A);
  printf("\n");

  // free memory associated with the big integer
  freeBigInteger(&A);
  freeBigInteger(&B);
  freeBigInteger(&C);
  freeBigInteger(&D);

  return 0;
}
