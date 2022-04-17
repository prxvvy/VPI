/* VPI - A program to automate the installation of Vim plugins with native
 * plugin manager. Copyright (C) 2022 prxvvy <qsk55464@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

static const char idepluginspath[] = "./.vim/pack/IDE/start";
static const char appearancepluginspath[] = "./.vim/pack/appearance/start";
static const char separator[] = ";";
static const char *plugins[] = {"neoclide;coc.nvim;ide",
                                "sainnhe;gruvbox-material;appearance"};
