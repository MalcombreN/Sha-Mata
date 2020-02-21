# Sha-Mata 

## Présentation

Projet de fin de licence 3 fais à l'université d'Angers

Réalise par :
- MA Tianning
- MALCOMBRE Nicolas

Encadré par :
- STEPHAN Igor

## Droits

### Fichiers présent dans le dossier `sources/`
Les fichiers du solveur mini SAT doivent être utilisés selon les règles suivantes imposées par les créateurs :

```
including without limitation the rights to use, copy, modify, merge, publish, distribute,
sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or
substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT
NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT
OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
```

Tous les autres fichiers ou parties de code peuvent être utilisés, modifiés, diffusés pour n'importe quel usage. 
**Nous ne garantissons pas et en aucun cas l'usage que vous en ferez.**

### Le rapport 

L'usage du rapport doit respecter strictement la [license by-nc-nd 2.0](https://creativecommons.org/licenses/by-nc-nd/2.0/fr/)

## Utilisation

Ce projet est fais pour être utilisé sur un OS de type *Linux*

Une fois les sources rappatriées sur votre ordinateur, assurez vous que les librairies *freeglut3-dev* et *zlib1g-dev* soient installées.

Ouvrez un terminal dans le répertoire `sources/` :

Tapez les commandes suivantes pour compiler, créer l'executable, et lancer le jeu :
``` bash
make
./exe &
```

L'éxécutable ne doit pas être déplacé pour fonctionner. Si vous voulez créer un lien sur votre Bureau taper la commande suivante :
``` bash
ln -s exe ~/Desktop/ShaMata
```
