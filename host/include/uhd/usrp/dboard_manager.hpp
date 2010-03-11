//
// Copyright 2010 Ettus Research LLC
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//

#ifndef INCLUDED_UHD_USRP_DBOARD_MANAGER_HPP
#define INCLUDED_UHD_USRP_DBOARD_MANAGER_HPP

#include <uhd/props.hpp>
#include <uhd/usrp/dboard_base.hpp>
#include <uhd/usrp/dboard_id.hpp>
#include <boost/utility.hpp>
#include <boost/shared_ptr.hpp>

namespace uhd{ namespace usrp{

/*!
 * A daughter board subdev dboard_manager class.
 * Create subdev instances for each subdev on a dboard.
 * Provide wax::obj access to the subdevs inside.
 */
class dboard_manager : boost::noncopyable{

public:
    typedef boost::shared_ptr<dboard_manager> sptr;

    //dboard constructor (each dboard should have a ::make with this signature)
    typedef dboard_base::sptr(*dboard_ctor_t)(dboard_base::ctor_args_t const&);

    /*!
     * Register subdevices for a given dboard id.
     *
     * \param dboard_id the dboard id (rx or tx)
     * \param dboard_ctor the dboard constructor function pointer
     * \param name the canonical name for the dboard represented
     * \param subdev_names the names of the subdevs on this dboard
     */
    static void register_subdevs(
        dboard_id_t dboard_id,
        dboard_ctor_t dboard_ctor,
        const std::string &name,
        const prop_names_t &subdev_names
    );

    /*!
     * Make a new dboard manager.
     * \param rx_dboard_id the id of the rx dboard
     * \param tx_dboard_id the id of the tx dboard
     * \param interface the custom dboard interface
     * \return an sptr to the new dboard manager
     */
    static sptr make(
        dboard_id_t rx_dboard_id,
        dboard_id_t tx_dboard_id,
        dboard_interface::sptr interface
    );

    //dboard_interface
    virtual prop_names_t get_rx_subdev_names(void) = 0;
    virtual prop_names_t get_tx_subdev_names(void) = 0;
    virtual wax::obj get_rx_subdev(const std::string &subdev_name) = 0;
    virtual wax::obj get_tx_subdev(const std::string &subdev_name) = 0;
};

}} //namespace

#endif /* INCLUDED_UHD_USRP_DBOARD_MANAGER_HPP */
